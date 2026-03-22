#ifndef _NERAME_HPP_
#define _NERAME_HPP_

typedef struct NodesEditor NodesEditor;

class NEFrame {
private:
    NodesEditor* nodesEditor;

public:
    NEFrame(NodesEditor* nodesEditor);
    void draw(int width, int height);
};

#endif // _NERAME_HPP_