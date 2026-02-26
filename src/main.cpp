#include <wx/wx.h>
#include "ui/MainFrame.hpp"

class App : public wxApp
{
public:
    bool OnInit() override
    {
        auto *frame = new MainFrame();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(App);