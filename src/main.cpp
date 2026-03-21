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

void fillFonts(ImGuiIO* io);

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
    std::string shaderPath
){
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

void fillFonts(ImGuiIO* io)
{
    Font::arial_18 = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 18); // Стандартный шрифт

    Font::arial_16 = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 16);
    Font::arial_20 = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 20);
    Font::arial_22 = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 22);
    Font::arial_24 = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 24);

    Font::calibri_16 = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Calibri.ttf", 16);
    Font::calibri_18 = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Calibri.ttf", 18);
    Font::calibri_20 = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Calibri.ttf", 20);
    Font::calibri_22 = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Calibri.ttf", 22);
    Font::calibri_24 = io->Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Calibri.ttf", 24);
}
