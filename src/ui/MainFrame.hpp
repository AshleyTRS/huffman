#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "TreePanel.hpp"

class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
    void OnEncode(wxCommandEvent &event);

    wxTextCtrl *inputCtrl_;
    wxListCtrl *freqTable_;
    wxListCtrl *codesTable_;
    wxScrolledWindow *scrolledWindow_;
    TreePanel *treePanel_;
    wxTextCtrl *encodedOutput_;
};
