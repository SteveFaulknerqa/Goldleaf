#include "ui/install_view.hpp"

#include <memory>
#include "ui/framework/canvas.hpp"
#include "ui/framework/box_element.hpp"
#include "ui/framework/text_element.hpp"
#include "ui/framework/font_renderer.hpp"

namespace tin::ui
{
    InstallView::InstallView()
    {
        auto backgroundLayer = std::make_unique<Layer>("background");
        auto foregroundLayer = std::make_unique<Layer>("foreground");

        // Background
        auto backgroundBox = std::make_unique<BoxElement>(1280, 720);
        backgroundBox->SetColour(tin::ui::Colour(0x394566));
        backgroundLayer->AddElement(std::move(backgroundBox), 0, 0);

        // Foreground
        auto sidebarBox = std::make_unique<BoxElement>(120, 720);
        sidebarBox->SetColour(tin::ui::Colour(0x2B334F));
        foregroundLayer->AddElement(std::move(sidebarBox), 0, 0);

        // Header
        auto headerBox = std::make_unique<BoxElement>(1280-120, 80);
        SubElementLayout headerSubElementLayout;
        headerSubElementLayout.arrangementType = SubElementArrangementType::LEFT_TO_RIGHT;
        headerSubElementLayout.leftInset = 25;
        headerSubElementLayout.bottomInset = 27;
        headerBox->SetColour(tin::ui::Colour(0x556C91));
        headerBox->SetSubElementLayout(headerSubElementLayout);

        auto installApplicationText = std::make_unique<TextElement>(0, 0);
        installApplicationText->SetText("Install Application");
        installApplicationText->SetScale(6);

        headerBox->AddSubElement(std::move(installApplicationText));
        foregroundLayer->AddElement(std::move(headerBox), 120, 0);

        // Game list
        auto gameListBox = std::make_unique<BoxElement>(625, 720-80);
        gameListBox->SetColour(0x394566);

        SubElementLayout gameListSubElementLayout;
        gameListSubElementLayout.arrangementType = SubElementArrangementType::TOP_TO_BOTTOM;
        gameListBox->SetSubElementLayout(gameListSubElementLayout);

        auto rowElement = std::make_unique<BoxElement>(0, 80);
        SubElementLayout rowSubElementLayout;
        rowSubElementLayout.arrangementType = SubElementArrangementType::BOTTOM_TO_TOP;
        rowElement->SetColour(0x394566);
        rowElement->SetSubElementLayout(rowSubElementLayout);

        auto underlineElement = std::make_unique<BoxElement>(0, 3);
        underlineElement->SetColour(0x556C91);
        rowElement->AddSubElement(std::move(underlineElement));

        
        gameListBox->AddSubElement(std::move(rowElement));
        foregroundLayer->AddElement(std::move(gameListBox), 120+25, 80);

        this->AddLayer(std::move(backgroundLayer));
        this->AddLayer(std::move(foregroundLayer));
    }

    void InstallView::Update()
    {
        LayoutView::Update();
    }
}