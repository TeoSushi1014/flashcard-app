// Set file encoding to UTF-8
#pragma execution_character_set("utf-8")

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::flashcard_app::implementation
{
    void MainWindow::ShowStatus(winrt::hstring const& message, InfoBarSeverity severity)
    {
        StatusBar().Message(message);
        StatusBar().Severity(severity);
        StatusBar().IsOpen(true);
    }

    void MainWindow::UpdateUI()
    {
        if (!m_list) return;

        Node* current = m_list->getCurrent();
        int currentIdx = m_list->getCurrentIndex();
        int size = m_list->getSize();

        if (current && currentIdx >= 0) {
            // Dùng trực tiếp std::wstring, không cần convert
            CurrentCardText().Text(current->data);
            winrt::hstring indexText = L"Vị trí: " + winrt::to_hstring(currentIdx) + L"/" + winrt::to_hstring(size - 1);
            CardIndexText().Text(indexText);
        } else {
            CurrentCardText().Text(L"Chưa có thẻ");
            CardIndexText().Text(L"Vị trí: -/-");
        }

        // Update list display
        if (size == 0) {
            ListDisplay().Text(L"Danh sách trống");
        } else {
            // Dùng trực tiếp std::wstring, không cần convert
            ListDisplay().Text(m_list->getAllCardsAsString());
        }
    }

    void MainWindow::Previous_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        int currentIdx = m_list->getCurrentIndex();
        if (currentIdx > 0) {
            m_list->setCurrentIndex(currentIdx - 1);
            UpdateUI();
            ShowStatus(L"Đã chuyển đến thẻ trước", InfoBarSeverity::Success);
        } else {
            ShowStatus(L"Đã ở thẻ đầu tiên", InfoBarSeverity::Warning);
        }
    }

    void MainWindow::Next_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        int currentIdx = m_list->getCurrentIndex();
        int size = m_list->getSize();
        
        if (currentIdx < size - 1) {
            m_list->setCurrentIndex(currentIdx + 1);
            UpdateUI();
            ShowStatus(L"Đã chuyển đến thẻ sau", InfoBarSeverity::Success);
        } else {
            ShowStatus(L"Đã ở thẻ cuối cùng", InfoBarSeverity::Warning);
        }
    }

    void MainWindow::AddToEnd_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        winrt::hstring input = NewCardInput().Text();
        std::wstring value{ input };

        if (value.empty()) {
            ShowStatus(L"Vui lòng nhập từ vựng", InfoBarSeverity::Warning);
            return;
        }

        m_list->append(value);
        NewCardInput().Text(L"");
        UpdateUI();
        ShowStatus(L"Đã thêm thẻ vào cuối danh sách", InfoBarSeverity::Success);
    }

    void MainWindow::AddToStart_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        winrt::hstring input = NewCardInput().Text();
        std::wstring value{ input };

        if (value.empty()) {
            ShowStatus(L"Vui lòng nhập từ vựng", InfoBarSeverity::Warning);
            return;
        }

        m_list->prepend(value);
        NewCardInput().Text(L"");
        UpdateUI();
        ShowStatus(L"Đã thêm thẻ vào đầu danh sách", InfoBarSeverity::Success);
    }

    void MainWindow::Delete_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        winrt::hstring input = DeleteCardInput().Text();
        std::wstring value{ input };

        if (value.empty()) {
            ShowStatus(L"Vui lòng nhập từ cần xóa", InfoBarSeverity::Warning);
            return;
        }

        if (m_list->deleteNode(value)) {
            DeleteCardInput().Text(L"");
            UpdateUI();
            ShowStatus(L"Đã xóa thẻ thành công", InfoBarSeverity::Success);
        } else {
            ShowStatus(L"Không tìm thấy thẻ để xóa", InfoBarSeverity::Error);
        }
    }

    void MainWindow::Find_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        int index = static_cast<int>(FindIndexInput().Value());
        Node* found = m_list->findByIndex(index);

        if (found) {
            UpdateUI();
            ShowStatus(L"Đã tìm thấy thẻ tại vị trí " + winrt::to_hstring(index), InfoBarSeverity::Success);
        } else {
            ShowStatus(L"Không tìm thấy thẻ tại vị trí " + winrt::to_hstring(index), InfoBarSeverity::Error);
        }
    }

    void MainWindow::TraverseForward_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        int size = m_list->getSize();
        if (size == 0) {
            ListDisplay().Text(L"Danh sách trống");
        } else {
            // Dùng trực tiếp std::wstring, không cần convert
            ListDisplay().Text(m_list->getAllCardsAsString());
        }
        ShowStatus(L"Đã duyệt danh sách từ đầu đến cuối", InfoBarSeverity::Informational);
    }

    void MainWindow::TraverseBackward_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        int size = m_list->getSize();
        if (size == 0) {
            ListDisplay().Text(L"Danh sách trống");
        } else {
            // Dùng trực tiếp std::wstring, không cần convert
            ListDisplay().Text(m_list->getAllCardsAsStringReverse());
        }
        ShowStatus(L"Đã duyệt danh sách từ cuối về đầu", InfoBarSeverity::Informational);
    }
}
