#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "Platform.hpp"
#include <GLFW/glfw3.h>
#include <imnodes/imnodes.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "NeFrame/WindowNE.hpp"
#include "NeFrame/NEFrame.hpp"
#include "NEFrame/NodesEditor/ControlPanel/ControlPanel.hpp"
#include "NEFrame/NodesDB/NodesDB.hpp"
#include "NEFrame/Linker/Linker.hpp"
#include "NEFrame/NodesEditor/NodesEditor.hpp"
#include "NEFrame/NodesEditor/Nodes/Node/NodeBuilder.hpp"
#include "NEFrame/NodesEditor/Nodes/IntStorage/IntStorage.hpp"
#include "NEFrame/NodesEditor/Nodes/FloatStorage/FloatStorage.hpp"
#include "NEFrame/NodesEditor/Nodes/ColorEditor/ColorEditor.hpp"
#include "NEFrame/NodesEditor/Nodes/MultStrEditor/MultStrEditor.hpp"
#include "NEFrame/NodesEditor/Nodes/FPSNode/FPSNode.hpp"

#include "FileHandler.hpp"

void fillControlPanel(
    ControlPanel* controlPanel,
    FileHandler* fileHandler,
    std::string shaderPath
);

int main(void)
{
    Platform plt(800, 600, "12");

    const std::string shaderPath = "shaderTXT.txt";
    FileHandler* fileHangler = new FileHandler();

    NodesDB* nodesDB = new NodesDB();
    Linker* linker = new Linker(nodesDB);

    ControlPanel* controlPanel = new ControlPanel(
        ImVec2(250, 120),
        nodesDB,
        linker
    );

    fillControlPanel(
        controlPanel,
        fileHangler,
        shaderPath
    ); // заполнение контрольной панели builder'ами нодов

    NodesEditor* nodesEditor = new NodesEditor(nodesDB, linker, controlPanel);
    NEFrame* neFrame = new NEFrame(nodesEditor);

    plt.onUpdate([neFrame](int width, int height) {
        neFrame->draw(width, height);
    });

    while (!plt.shouldClose()) {
        plt.render();
    }
    
    delete nodesDB;
    delete linker;
    delete controlPanel;
    delete nodesEditor;
    delete neFrame;
    delete fileHangler;

    return 0;
}

void fillControlPanel(
    ControlPanel* controlPanel, 
    FileHandler* fileHandler,
    std::string shaderPath)
{
    controlPanel->addNodeBuilder(
        NodeBuilder(
            []() {return std::make_shared<IntStorage>();  },
            IntStorage::CLASS_NAME
        )
    );

    controlPanel->addNodeBuilder(
        NodeBuilder(
            []() {return std::make_shared<FloatStorage>();  },
            FloatStorage::CLASS_NAME
        )
    );

    controlPanel->addNodeBuilder(
        NodeBuilder(
            []() {return std::make_shared<ColorEditor>();  },
            ColorEditor::CLASS_NAME
        )
    );

    controlPanel->addNodeBuilder(
        NodeBuilder(
            [fileHandler, shaderPath]() {return std::make_shared<MultStrEditor>(fileHandler, shaderPath);  },
            MultStrEditor::CLASS_NAME
        )
    );

    controlPanel->addNodeBuilder(
        NodeBuilder(
            []() {return std::make_shared<FPSNode>();  },
            FPSNode::CLASS_NAME
        )
    );
}
