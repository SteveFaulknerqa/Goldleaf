#include "ui/view.hpp"

namespace tin::ui
{
    ViewManager::ViewManager() {}

    ViewManager& ViewManager::Instance()
    {
        static ViewManager instance;
        return instance;
    }

    void ViewManager::PushView(std::unique_ptr<View> view)
    {
        if (m_views.size() > 0)
        {
            view->m_prevView = this->GetCurrentView();
        }

        view->m_viewManager = this;
        view->OnPresented();
        m_views.push(std::move(view));
    }

    void ViewManager::Unwind()
    {
        if (m_views.size() > 1)
            m_views.pop();

        this->GetCurrentView()->OnPresented();
    }

    void ViewManager::ProcessInput(u64 keys)
    {
        this->GetCurrentView()->ProcessInput(keys);
    }

    void ViewManager::Update()
    {
        this->GetCurrentView()->Update();
    }

    View* ViewManager::GetCurrentView()
    {
        return m_views.top().get();
    }
}