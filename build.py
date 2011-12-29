#! /usr/bin/python
import os
import re

def rebuild(dir):
    print ('Rebuilding ', dir)
    os.makedirs('.obj/' + dir[2:])

def needsBuilt(target, source): # Returns (needsBuilt, exists)
    try:
        return (os.stat(target).st_mtime < os.stat(source).st_mtime, False)
    except OSError:
        return (True, True)

def readDeps(_filename):
    try:
        return [dep.group(0) for dep in re.finditer(reg, open(_filename).read())]
    except IOError:
        return []

def compile(_target, _source):
    print ('Compiling ' + _target)
    os.system('gcc -c '+_source+' -o '+_target+' -std=c++0x -I .')
    output = os.popen('gcc -M ' + _source + ' -I .').read()
    deps = [dep.group(0) for dep in re.finditer(reg, output)]
    filename = '.deps' + _source[1:]
    try:
        file = open(filename)
        oldDeps = [dep.group(0) for dep in re.finditer(reg, file.read())]
    except IOError:
        oldDeps = []
    for dep in deps:
        if dep not in oldDeps:
            open('.deps/' + dep, 'a').write(_source[2:] + '\n')
    for dep in oldDeps:
        if dep not in deps:
            try:
                removedDepDeps = [newDep for newDep in readDeps('.deps/' + dep) if newDep != dep]
                removedDep = open('.deps/' + dep, 'w')
                for newDep in removedDepDeps:
                    removedDep.write(newDep + ' ')
                removedDep.write('\n')
            except IOError:
                pass

    
    try:
        file = open(filename, 'w')
    except IOError:
        index = filename.rfind('/', -1, 0)
        os.makedirs(filename[:index])
        file = open(filename, 'w')
    for dep in deps:
        file.write(dep + ' ')
    file.write('\n')

def headerBuild(_target, _source):
    deps = readDeps(_target)
    if _target == '.deps/Game.h':
        print (deps)
    for dep in deps:
        compile('.obj/' + dep[:-4] + '.o', dep)

files = []
gen = os.walk('.')
reg = re.compile(r'([a-zA-Z0-9]*.h)')
try:
    modTime = os.stat('a.out')
except OSError:
    modTime = 0
for dirpath, dirnames, filenames in gen:
    try:
        dirnames.remove('.deps')
        dirnames.remove('.git')
        dirnames.remove('.obj')
    except ValueError:
        pass
    for dir in dirnames:
        fullPath = dirpath + '/' + dir
        build = needsBuilt('.obj/'+fullPath, fullPath)
        if build[0]:
            if build[1]:
                rebuild(fullPath)
        else:
            dirnames.remove(dir)
    for file in filenames:
        source = dirpath + '/' + file
        if file[-4:] == '.cpp':
            target = '.obj/' + source[2:-4] + '.o'
            files += target
            if needsBuilt(target, source)[0]:
                compile(target, source)
        else:
            if file[-2:] == '.h' or file[-4:] == '.hpp':
                target = '.deps' + dirpath[1:] + '/' + file
                if os.stat(source).st_mtime > modTime:
                    headerBuild(target, source)


