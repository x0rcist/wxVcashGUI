/******************************************************************************
 * wxVcashGUI: a GUI for Vcash, a decentralized currency 
 *             for the internet (https://vcash.info).
 *
 * Copyright (c) The Vcash Developers
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 ******************************************************************************/
 
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/sizer.h>
#endif

#include "AddressesPage.h"
#include "ConsolePage.h"
#include "MiningPage.h"
#include "StatisticsPage.h"
#include "ToolsPanel.h"
#include "ToolsFrame.h"
#include "VcashApp.h"

using namespace wxGUI;

ToolsPanel::ToolsPanel(VcashApp &vcashApp, wxWindow &parent)
        : wxPanel(&parent, wxID_ANY) {

    notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxT("ToolsPanel"));

    notebook->AddPage(new StatisticsPage(vcashApp, *notebook), wxT("Statistics"));
    notebook->AddPage(new AddressesPage(vcashApp, *notebook), wxT("Addresses"));
    notebook->AddPage(new ConsolePage(vcashApp, *notebook), wxT("Console"));
    notebook->AddPage(new MiningPage(vcashApp, *notebook), wxT("Mining"));

    vcashApp.view.toolsPanel = this;

    wxSizer *sizerV = new wxBoxSizer(wxVERTICAL);
    sizerV->Add(notebook, 1    // make horizontally stretchable
            , wxALL | wxEXPAND // make border all around & fill parent
            , 10               // border size
    );
    SetSizerAndFit(sizerV);

    notebook->Bind(wxEVT_CHAR, [&vcashApp](wxKeyEvent &ev) {
        if(ev.GetKeyCode() == WXK_ESCAPE)
            vcashApp.view.hideToolsFrame();
        ev.Skip();
    });
}

void ToolsPanel::showPage(ToolsPage page) {
    switch (page) {
        case ToolsPage::Statistics: {
            notebook->SetSelection(0);
            break;
        }
        case ToolsPage::Addresses: {
            notebook->SetSelection(1);
            break;
        }
        case ToolsPage::Console: {
            notebook->SetSelection(2);
            break;
        }
        case ToolsPage::Mining: {
            notebook->SetSelection(3);
            break;
        }
    }
    GetParent()->Show(true);
}

