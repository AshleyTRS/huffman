#include "MainFrame.hpp"
#include "../core/Huffman.hpp"

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "PROGRAMA DE CODIFICACIÓN DE HUFFMAN", wxDefaultPosition, wxSize(800, 600))
{

    scrolledWindow_ = new wxScrolledWindow(this);
    scrolledWindow_->SetScrollRate(10, 10);

    auto *sizer = new wxBoxSizer(wxVERTICAL);

    inputCtrl_ = new wxTextCtrl(
        scrolledWindow_,
        wxID_ANY,
        "",
        wxDefaultPosition,
        wxSize(-1, 100),
        wxTE_MULTILINE | wxTE_WORDWRAP);
    auto *button = new wxButton(scrolledWindow_, wxID_ANY, "Codificar",
                                wxDefaultPosition, wxSize(120, 40));

    freqTable_ = new wxListCtrl(scrolledWindow_, wxID_ANY,
                                wxDefaultPosition, wxSize(220, 200),
                                wxLC_REPORT | wxLC_SINGLE_SEL);

    freqTable_->InsertColumn(0, "Símbolo", wxLIST_FORMAT_CENTER, 60);
    freqTable_->InsertColumn(1, "Frecuencia", wxLIST_FORMAT_CENTER, 120);

    codesTable_ = new wxListCtrl(scrolledWindow_, wxID_ANY,
                                 wxDefaultPosition, wxSize(220, 200),
                                 wxLC_REPORT | wxLC_SINGLE_SEL);

    codesTable_->InsertColumn(0, "Símbolo", wxLIST_FORMAT_CENTER, 60);
    codesTable_->InsertColumn(1, "Símbolo Codificado", wxLIST_FORMAT_CENTER, 140);

    encodedOutput_ = new wxTextCtrl(
        scrolledWindow_,
        wxID_ANY,
        "",
        wxDefaultPosition,
        wxSize(-1, 100),
        wxTE_MULTILINE | wxTE_READONLY | wxTE_WORDWRAP);

    treePanel_ = new TreePanel(scrolledWindow_);
    treePanel_->SetMinSize(wxSize(2000, 1200));

    sizer->Add(inputCtrl_, 0, wxEXPAND | wxALL, 5);
    sizer->Add(button, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(new wxStaticText(scrolledWindow_, wxID_ANY, "Tabla de Frecuancias"), 0, wxLEFT, 5);
    sizer->Add(freqTable_, 0, wxEXPAND | wxALL, 5);
    sizer->Add(new wxStaticText(scrolledWindow_, wxID_ANY, "Símbolos Codificados"), 0, wxLEFT, 5);
    sizer->Add(codesTable_, 0, wxEXPAND | wxALL, 5);
    sizer->Add(new wxStaticText(scrolledWindow_, wxID_ANY, "Cadena Codificada"), 0, wxLEFT, 5);
    sizer->Add(encodedOutput_, 0, wxEXPAND | wxALL, 5);
    sizer->Add(treePanel_, 1, wxEXPAND | wxALL, 5);

    scrolledWindow_->SetSizer(sizer);
    scrolledWindow_->FitInside();

    button->Bind(wxEVT_BUTTON, &MainFrame::OnEncode, this);
}

void MainFrame::OnEncode(wxCommandEvent &)
{
    freqTable_->DeleteAllItems();
    codesTable_->DeleteAllItems();

    std::string input = inputCtrl_->GetValue().ToStdString();
    Huffman h(input);

    int i = 0;
    for (const auto &f : h.frequency_table())
    {
        freqTable_->InsertItem(i, std::string(1, f.symbol));
        freqTable_->SetItem(i, 1, std::to_string(f.freq));
        i++;
    }

    i = 0;
    for (const auto &[symbol, code] : h.codes())
    {
        codesTable_->InsertItem(i, std::string(1, symbol));
        codesTable_->SetItem(i, 1, code);
        i++;
    }

    std::string encoded = h.encode();
    encodedOutput_->SetValue(encoded);

    treePanel_->SetTree(h.root());
}