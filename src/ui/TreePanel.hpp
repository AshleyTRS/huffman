#pragma once
#include <wx/wx.h>
#include "../core/Huffman.hpp"

class TreePanel : public wxPanel
{
public:
    explicit TreePanel(wxWindow *parent);

    void SetTree(Huffman::Node *root);

private:
    void OnPaint(wxPaintEvent &event);
    void DrawTree(wxDC &dc, Huffman::Node *node,
                  int x, int y, int horizontalSpacing);

    Huffman::Node *root_;
};