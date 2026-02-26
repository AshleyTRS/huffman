#include "TreePanel.hpp"
#include <wx/dcbuffer.h>

TreePanel::TreePanel(wxWindow *parent)
    : wxPanel(parent), root_(nullptr)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT); // reduces flicker
    Bind(wxEVT_PAINT, &TreePanel::OnPaint, this);
}

void TreePanel::SetTree(Huffman::Node *root)
{
    root_ = root;

    // For now fixed size (later we can compute dynamically)
    int width = 2000;
    int height = 1500;

    SetMinSize(wxSize(width, height));

    if (auto *scrolled = wxDynamicCast(GetParent(), wxScrolledWindow))
    {
        scrolled->FitInside();
        scrolled->Layout();
    }

    Refresh();
}

void TreePanel::OnPaint(wxPaintEvent &)
{
    wxAutoBufferedPaintDC dc(this); // double buffering
    PrepareDC(dc);                  // important for scrolling
    dc.Clear();

    if (!root_)
        return;

    int width = GetSize().GetWidth();

    // Prevent spacing from becoming 0
    int initialSpacing = std::max(width / 4, 60);

    DrawTree(dc, root_, width / 2, 60, initialSpacing);
}

void TreePanel::DrawTree(wxDC &dc, Huffman::Node *node,
                         int x, int y, int spacing)
{
    if (!node)
        return;

    const int radius = 25;
    const int verticalSpacing = 100;

    // ---- Left child ----
    if (node->left)
    {
        int childX = x - spacing;
        int childY = y + verticalSpacing;

        dc.DrawLine(x, y, childX, childY);

        wxString edgeLabel = "0";
        wxSize edgeSize = dc.GetTextExtent(edgeLabel);

        dc.DrawText(edgeLabel,
                    (x + childX) / 2 - edgeSize.GetWidth() / 2,
                    (y + childY) / 2 - edgeSize.GetHeight() / 2);

        DrawTree(dc, node->left, childX, childY, std::max(spacing / 2, 40));
    }

    // ---- Right child ----
    if (node->right)
    {
        int childX = x + spacing;
        int childY = y + verticalSpacing;

        dc.DrawLine(x, y, childX, childY);

        wxString edgeLabel = "1";
        wxSize edgeSize = dc.GetTextExtent(edgeLabel);

        dc.DrawText(edgeLabel,
                    (x + childX) / 2 - edgeSize.GetWidth() / 2,
                    (y + childY) / 2 - edgeSize.GetHeight() / 2);

        DrawTree(dc, node->right, childX, childY, std::max(spacing / 2, 40));
    }

    // ---- Draw node circle ----
    dc.DrawCircle(x, y, radius);

    wxString label;
    if (!node->left && !node->right)
        label = wxString::Format("%c (%lld)", node->symbol, node->freq);
    else
        label = wxString::Format("%lld", node->freq);

    wxSize textSize = dc.GetTextExtent(label);

    dc.DrawText(label,
                x - textSize.GetWidth() / 2,
                y - textSize.GetHeight() / 2);
}