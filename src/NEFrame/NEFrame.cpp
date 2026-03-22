#include "NEFrame.hpp"
#include <imgui/imgui.h>

#include <list>
#include <memory>
#include <functional>
#include <unordered_map>
#include <exception>

#include "NEFrame/NodesDB/NodesDB.hpp"
#include "NEFrame/NodesEditor/Nodes/Node/Node.hpp"
#include "NEFrame/Formating/LinkInfo.hpp"
#include "NodesEditor/NodesEditor.hpp"

NEFrame::NEFrame(NodesEditor* nodesEditor) {
    this->nodesEditor = nodesEditor;

}

void NEFrame::draw(int width, int height) {
    ImVec2 LeftUp = ImVec2(0, 0);
    ImVec2 RightDown = ImVec2(width, height);
    this->nodesEditor->draw(&LeftUp, &RightDown);
}
