#include "DynamicEditor.h"
#include <Graphics/Camera/FreeCamera.h>
#include <AbstractFactory/AbstractFactories.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Entity.h>
#include <Physics/PhysicsManager.h>
#include <GameModes/Editor/DynamicEditor/AllDynamicEditorVariableTypes.h>
#include <AbstractFactory/FactoryLoaders/TextFileFactoryLoader.h>
std::vector<std::pair<std::vector<std::string>,DynamicEditor::ModeFactory*>> DynamicEditor::editorModes
({
    {
        {"position","dimensions"}, new DynamicEditor::DerivedModeFactory<BoxDragVariable>()
    }
 });
std::unordered_map<std::string, DynamicEditor::VariableFactory*> DynamicEditor::editorVariables
({
    {
        "material", new DynamicEditor::DerivedVariableFactory<TextEditBox>()
    }
 });

DynamicEditor::DynamicEditor(FreeCamera* camera)
{
    //ctor
    camera->activate();
    mCamera = camera;
}

DynamicEditor::~DynamicEditor()
{
    //dtor
}
#include <iostream>
void DynamicEditor::init()
{
    activeEditor = createEditorMode("CrateFactory");
}

DynamicEditorMode* DynamicEditor::createEditorMode(const std::string& factoryName)
{
    AbstractFactoryBase<Entity>* factory = AbstractFactories::global().getFactory<Entity>(factoryName);
    BoxDragVariable* editor = nullptr;
    {
        FactoryParameters parameters(true);
        g_PhysicsManager.destroyBody(factory->use(&parameters)->mBody);
        std::vector<std::string> values = parameters.getUndefinedLog(); /// FIXME this could be faster, its stored as a map internally, we could sort it
        for (auto editorMode = editorModes.begin(); editorMode != editorModes.end(); editorMode++)
        {
            unsigned int matches = 0;
            std::vector<std::vector<std::string>::iterator> matchedStrings; /// Keep a track of these so we can delete them in case of a complete match
            for (auto string = editorMode->first.begin(); string != editorMode->first.end(); string++)
            {
                for (auto value = values.begin(); value != values.end(); value++)
                {
                    if (*value == *string)
                    {
                        matches++;
                        matchedStrings.push_back(value);
                        break;
                    }
                }
            }
            if (matches == values.size())
            {
                editor = new BoxDragVariable();
                editor->initEditorMode(factoryName);
                editor->initEditorVariable(this, &params);
                while (!matchedStrings.empty())
                {
                    values.erase(matchedStrings.back());
                    matchedStrings.pop_back();
                }
                break;
            }
            /// else matchedStrings.clear(); - Not necessary
        }
    }
    {
        TextFileFactoryLoader loader(nullptr, true);
        factory->init(&loader, &AbstractFactories::global());
        std::vector<std::string> values = loader.getUndefinedLog();
        for (auto value = values.begin(); value != values.end(); value++)
        {
            auto variable = editorVariables.find(*value);
            if (variable != editorVariables.end())
            {
                editor->addVariable(variable->second->createVariable());
            }
        }
    }
    return editor;
}

void DynamicEditor::buttonDown(Vec2i mouse, unsigned char button)
{
    activeEditor->buttonDown(mouse,button);
}
void DynamicEditor::mouseMove(Vec2i mouse)
{
    activeEditor->mouseMove(mouse);
}
void DynamicEditor::buttonUp(Vec2i mouse, unsigned char button)
{
    activeEditor->buttonUp(mouse,button);
}
