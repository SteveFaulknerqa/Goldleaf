#include "ui/framework/layer.hpp"

#include "error.hpp"

namespace tin::ui
{
    Layer::Layer(std::string name) :
        m_name(name)
    {

    }

    void Layer::DrawLayer()
    {
        for (auto& entry : m_elementEntries)
        {
            entry->element->DrawElement(entry->position, Dimensions(1280, 720));
        }
    }

    std::string Layer::GetName()
    {
        return m_name;
    }

    void Layer::AddElement(std::unique_ptr<Element> element, unsigned int x, unsigned int y)
    {
        auto entry = std::make_unique<ElementEntry>(std::move(element), Position(x, y));
        m_elementEntries.push_back(std::move(entry));
    }
}