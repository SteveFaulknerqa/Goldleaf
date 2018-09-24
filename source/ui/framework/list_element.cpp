#include "ui/framework/list_element.hpp"

#include "error.hpp"

namespace tin::ui
{
    RowElement::RowElement(u32 width) :
        BoxElement(width, ROW_HEIGHT)
    {
        SubElementLayout rowSubElementLayout;
        rowSubElementLayout.arrangementType = SubElementArrangementType::BOTTOM_TO_TOP;
        this->SetColour(Colour(0, 0, 0, 0));
        this->SetSubElementLayout(rowSubElementLayout);

        auto underlineElement = std::make_unique<BoxElement>(m_dimensions.width, 3);
        underlineElement->SetColour(0x556C91);
        this->AddSubElement(std::move(underlineElement));

        auto contentElement = std::make_unique<BoxElement>(m_dimensions.width, m_dimensions.height - 3);
        SubElementLayout contentSubElementLayout;
        contentSubElementLayout.arrangementType = SubElementArrangementType::LEFT_TO_RIGHT;
        contentElement->SetColour(Colour(0, 0, 0, 0));
        contentElement->SetSubElementLayout(contentSubElementLayout);

        auto textElement = std::make_unique<TextElement>(m_dimensions.width * 0.8, m_dimensions.height);
        textElement->SetScale(5);
        textElement->SetColour(0xC3D0DF);
        textElement->SetInsets(0, 30);
        m_textElement = textElement.get();

        contentElement->AddSubElement(std::move(textElement));
        this->AddSubElement(std::move(contentElement));
    }

    ListElement::ListElement(u32 width, u32 height) :
        BoxElement(width, height)
    {
        this->SetColour(Colour(0, 0, 0, 0));

        SubElementLayout subElementLayout;
        subElementLayout.arrangementType = SubElementArrangementType::TOP_TO_BOTTOM;
        this->SetSubElementLayout(subElementLayout);

        m_touchHandler.m_onTouchesStarted = [&](unsigned int posX, unsigned int posY)
        {
            m_startScrollOffset = m_scrollOffset;
        };

        m_touchHandler.m_onTouchesMoving = [&](unsigned int startX, unsigned int startY, signed int distX, unsigned int distY)
        {
            LOG_DEBUG("Touches moving. %i %i\n", distX, distY);
        };

        m_touchHandler.m_onTapped = [&](unsigned int posX, unsigned int posY)
        {
            LOG_DEBUG("Touched. %u %u\n", posX, posY);
        };
    }

    unsigned int time = 0;

    void ListElement::Draw(Canvas canvas, Position position)
    {
        // No need to draw sub elements if we don't have any
        if (m_subElements.empty())
            return;

        time++;

        if (time >= 2)
        {
            m_scrollOffset += 1;
            time = 0;
        }

        if (m_scrollOffset < 0)
            m_scrollOffset = 0;

        // Subtract 3 to cut off the final underline
        unsigned int maxScroll = RowElement::ROW_HEIGHT * m_subElements.size() - m_dimensions.height - 3;

        LOG_DEBUG("Max Scroll: %u, Scroll: %u\n", maxScroll, m_scrollOffset);

        if (m_scrollOffset > maxScroll)
            m_scrollOffset = maxScroll;

        Position scrollPos = position;
        scrollPos.y = position.y - m_scrollOffset;
            
        unsigned int startOffset = 0;

        for (auto& subElement : m_subElements)
        {
            unsigned int startX = scrollPos.x;
            unsigned int startY = scrollPos.y + startOffset;

            Position subElementPos(startX, startY);
            // NOTE: The canvas is still whilst the list itself moves
            Canvas subElementCanvas = canvas.Intersect(position, this->GetDimensions()).Intersect(subElementPos, subElement->GetDimensions());
            
            subElement->Draw(subElementCanvas, subElementPos);
            startOffset += subElement->GetDimensions().height + m_subElementLayout.gapSize;
        }
    }

    void ListElement::Update(Position position)
    {
        m_touchHandler.SetTouchArea(position, m_dimensions);
        m_touchHandler.Update();
    }

    void ListElement::AddRow(const char* text)
    {
        auto rowElement = std::make_unique<RowElement>(m_dimensions.width);
        rowElement->m_textElement->SetText(text);
        this->AddSubElement(std::move(rowElement));
    }
}