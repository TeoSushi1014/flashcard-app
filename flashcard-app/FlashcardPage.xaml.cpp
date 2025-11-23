// Set file encoding to UTF-8
#pragma execution_character_set("utf-8")

#include "pch.h"
#include "FlashcardPage.xaml.h"
#include "LanguageConfig.h"
#include <chrono>
#if __has_include("FlashcardPage.g.cpp")
#include "FlashcardPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::flashcard_app::implementation
{
    void FlashcardPage::Page_Loaded(
        [[maybe_unused]] IInspectable const& sender,
        [[maybe_unused]] RoutedEventArgs const& args)
    {
        // Update language texts when page is loaded
        UpdateLanguageTexts();
        UpdateUI();
    }

    void FlashcardPage::UpdateLanguageTexts()
    {
        if (g_currentLanguage == AppLanguage::Vietnamese)
        {
            // Vietnamese texts
            AddToEndButton().Content(winrt::box_value(L"Thêm cuối"));
            AddToStartButton().Content(winrt::box_value(L"Thêm đầu"));
            DeleteButton().Content(winrt::box_value(L"Xóa"));
            FindButton().Content(winrt::box_value(L"Tìm"));
            PreviousButtonText().Text(L"Trước");
            NextButtonText().Text(L"Sau");
            TraverseForwardButtonText().Text(L"Duyệt xuôi");
            TraverseBackwardButtonText().Text(L"Duyệt ngược");
            CurrentCardLabel().Text(L"Thẻ từ vựng hiện tại");
            NewCardInput().PlaceholderText(L"Nhập từ vựng...");
            DeleteCardInput().PlaceholderText(L"Nhập từ cần xóa...");
            FindIndexInput().PlaceholderText(L"Nhập vị trí (0,1,2...)");
            AddCardSectionLabel().Text(L"Thêm thẻ mới");
            DeleteCardSectionLabel().Text(L"Xóa thẻ");
            FindCardSectionLabel().Text(L"Tìm thẻ");
            TraverseSectionLabel().Text(L"Duyệt danh sách");
            ListSectionLabel().Text(L"Danh sách thẻ");
            PerformanceTestSectionLabel().Text(L"Performance Test");
            PerformanceTestDescription().Text(L"Test hiệu năng với các kích thước khác nhau");
            Test10Button().Content(winrt::box_value(L"Test 10"));
            Test100Button().Content(winrt::box_value(L"Test 100"));
            Test1000Button().Content(winrt::box_value(L"Test 1,000"));
            Test10000Button().Content(winrt::box_value(L"Test 10,000"));
            TestResultText().Text(L"Chưa có kết quả test. Click nút test để bắt đầu.");
        }
        else
        {
            // English texts
            AddToEndButton().Content(winrt::box_value(L"Add to end"));
            AddToStartButton().Content(winrt::box_value(L"Add to front"));
            DeleteButton().Content(winrt::box_value(L"Delete"));
            FindButton().Content(winrt::box_value(L"Find"));
            PreviousButtonText().Text(L"Previous");
            NextButtonText().Text(L"Next");
            TraverseForwardButtonText().Text(L"Traverse forward");
            TraverseBackwardButtonText().Text(L"Traverse backward");
            CurrentCardLabel().Text(L"Current flashcard");
            NewCardInput().PlaceholderText(L"Enter vocabulary...");
            DeleteCardInput().PlaceholderText(L"Enter word to delete...");
            FindIndexInput().PlaceholderText(L"Enter position (0,1,2...)");
            AddCardSectionLabel().Text(L"Add new card");
            DeleteCardSectionLabel().Text(L"Delete card");
            FindCardSectionLabel().Text(L"Find card");
            TraverseSectionLabel().Text(L"Traverse list");
            ListSectionLabel().Text(L"Card list");
            PerformanceTestSectionLabel().Text(L"Performance Test");
            PerformanceTestDescription().Text(L"Test performance with different sizes");
            Test10Button().Content(winrt::box_value(L"Test 10"));
            Test100Button().Content(winrt::box_value(L"Test 100"));
            Test1000Button().Content(winrt::box_value(L"Test 1,000"));
            Test10000Button().Content(winrt::box_value(L"Test 10,000"));
            TestResultText().Text(L"No test results yet. Click test button to start.");
        }
    }

    void FlashcardPage::ShowStatus(winrt::hstring const& message, InfoBarSeverity severity)
    {
        StatusBar().Message(message);
        StatusBar().Severity(severity);
        StatusBar().IsOpen(true);
    }

    void FlashcardPage::UpdateUI()
    {
        if (!m_list) return;

        Node* current = m_list->getCurrent();
        int currentIdx = m_list->getCurrentIndex();
        int size = m_list->getSize();

        if (current && currentIdx >= 0) {
            // Dùng trực tiếp std::wstring, không cần convert
            CurrentCardText().Text(current->data);
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                winrt::hstring indexText = L"Vị trí: " + winrt::to_hstring(currentIdx) + L"/" + winrt::to_hstring(size - 1);
                CardIndexText().Text(indexText);
            } else {
                winrt::hstring indexText = L"Position: " + winrt::to_hstring(currentIdx) + L"/" + winrt::to_hstring(size - 1);
                CardIndexText().Text(indexText);
            }
        } else {
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                CurrentCardText().Text(L"Chưa có thẻ");
                CardIndexText().Text(L"Vị trí: -/-");
            } else {
                CurrentCardText().Text(L"No card");
                CardIndexText().Text(L"Position: -/-");
            }
        }

        // Update list display
        if (size == 0) {
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ListDisplay().Text(L"Danh sách trống");
            } else {
                ListDisplay().Text(L"List is empty");
            }
        } else {
            // Dùng trực tiếp std::wstring, không cần convert
            ListDisplay().Text(m_list->getAllCardsAsString());
        }
    }

    void FlashcardPage::Previous_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        int currentIdx = m_list->getCurrentIndex();
        if (currentIdx > 0) {
            m_list->setCurrentIndex(currentIdx - 1);
            UpdateUI();
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ShowStatus(L"Đã chuyển đến thẻ trước", InfoBarSeverity::Success);
            } else {
                ShowStatus(L"Moved to previous card", InfoBarSeverity::Success);
            }
        } else {
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ShowStatus(L"Đã ở thẻ đầu tiên", InfoBarSeverity::Warning);
            } else {
                ShowStatus(L"Already at first card", InfoBarSeverity::Warning);
            }
        }
    }

    void FlashcardPage::Next_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        int currentIdx = m_list->getCurrentIndex();
        int size = m_list->getSize();
        
        if (currentIdx < size - 1) {
            m_list->setCurrentIndex(currentIdx + 1);
            UpdateUI();
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ShowStatus(L"Đã chuyển đến thẻ sau", InfoBarSeverity::Success);
            } else {
                ShowStatus(L"Moved to next card", InfoBarSeverity::Success);
            }
        } else {
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ShowStatus(L"Đã ở thẻ cuối cùng", InfoBarSeverity::Warning);
            } else {
                ShowStatus(L"Already at last card", InfoBarSeverity::Warning);
            }
        }
    }

    void FlashcardPage::AddToEnd_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        winrt::hstring input = NewCardInput().Text();
        std::wstring value{ input };

        if (value.empty()) {
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ShowStatus(L"Vui lòng nhập từ vựng", InfoBarSeverity::Warning);
            } else {
                ShowStatus(L"Please enter vocabulary", InfoBarSeverity::Warning);
            }
            return;
        }

        m_list->append(value);
        NewCardInput().Text(L"");
        UpdateUI();
        if (g_currentLanguage == AppLanguage::Vietnamese) {
            ShowStatus(L"Đã thêm thẻ vào cuối danh sách", InfoBarSeverity::Success);
        } else {
            ShowStatus(L"Added card to end of list", InfoBarSeverity::Success);
        }
    }

    void FlashcardPage::AddToStart_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        winrt::hstring input = NewCardInput().Text();
        std::wstring value{ input };

        if (value.empty()) {
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ShowStatus(L"Vui lòng nhập từ vựng", InfoBarSeverity::Warning);
            } else {
                ShowStatus(L"Please enter vocabulary", InfoBarSeverity::Warning);
            }
            return;
        }

        m_list->prepend(value);
        NewCardInput().Text(L"");
        UpdateUI();
        if (g_currentLanguage == AppLanguage::Vietnamese) {
            ShowStatus(L"Đã thêm thẻ vào đầu danh sách", InfoBarSeverity::Success);
        } else {
            ShowStatus(L"Added card to start of list", InfoBarSeverity::Success);
        }
    }

    void FlashcardPage::Delete_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        winrt::hstring input = DeleteCardInput().Text();
        std::wstring value{ input };

        if (value.empty()) {
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ShowStatus(L"Vui lòng nhập từ cần xóa", InfoBarSeverity::Warning);
            } else {
                ShowStatus(L"Please enter word to delete", InfoBarSeverity::Warning);
            }
            return;
        }

        if (m_list->deleteNode(value)) {
            DeleteCardInput().Text(L"");
            UpdateUI();
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ShowStatus(L"Đã xóa thẻ thành công", InfoBarSeverity::Success);
            } else {
                ShowStatus(L"Card deleted successfully", InfoBarSeverity::Success);
            }
        } else {
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ShowStatus(L"Không tìm thấy thẻ để xóa", InfoBarSeverity::Error);
            } else {
                ShowStatus(L"Card not found to delete", InfoBarSeverity::Error);
            }
        }
    }

    void FlashcardPage::Find_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        int index = static_cast<int>(FindIndexInput().Value());
        Node* found = m_list->findByIndex(index);

        if (found) {
            UpdateUI();
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ShowStatus(L"Đã tìm thấy thẻ tại vị trí " + winrt::to_hstring(index), InfoBarSeverity::Success);
            } else {
                ShowStatus(L"Found card at position " + winrt::to_hstring(index), InfoBarSeverity::Success);
            }
        } else {
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ShowStatus(L"Không tìm thấy thẻ tại vị trí " + winrt::to_hstring(index), InfoBarSeverity::Error);
            } else {
                ShowStatus(L"Card not found at position " + winrt::to_hstring(index), InfoBarSeverity::Error);
            }
        }
    }

    void FlashcardPage::TraverseForward_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        int size = m_list->getSize();
        if (size == 0) {
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ListDisplay().Text(L"Danh sách trống");
            } else {
                ListDisplay().Text(L"List is empty");
            }
        } else {
            // Dùng trực tiếp std::wstring, không cần convert
            ListDisplay().Text(m_list->getAllCardsAsString());
        }
        if (g_currentLanguage == AppLanguage::Vietnamese) {
            ShowStatus(L"Đã duyệt danh sách từ đầu đến cuối", InfoBarSeverity::Informational);
        } else {
            ShowStatus(L"Traversed list from start to end", InfoBarSeverity::Informational);
        }
    }

    void FlashcardPage::TraverseBackward_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        if (!m_list) return;

        int size = m_list->getSize();
        if (size == 0) {
            if (g_currentLanguage == AppLanguage::Vietnamese) {
                ListDisplay().Text(L"Danh sách trống");
            } else {
                ListDisplay().Text(L"List is empty");
            }
        } else {
            // Dùng trực tiếp std::wstring, không cần convert
            ListDisplay().Text(m_list->getAllCardsAsStringReverse());
        }
        if (g_currentLanguage == AppLanguage::Vietnamese) {
            ShowStatus(L"Đã duyệt danh sách từ cuối về đầu", InfoBarSeverity::Informational);
        } else {
            ShowStatus(L"Traversed list from end to start", InfoBarSeverity::Informational);
        }
    }

    void FlashcardPage::TestPerformance(int cardCount)
    {
        if (!m_list) return;

        m_list.reset();
        m_list = std::make_unique<DoublyLinkedList>();

        std::wstring result;
        result = L"Test " + std::to_wstring(cardCount) + L" thẻ:\n\n";

        {
            DoublyLinkedList warmup;
            for (int i = 0; i < 100; i++) {
                std::wstring warmupStr = L"Warmup " + std::to_wstring(i);
                warmup.append(warmupStr);
            }
        }

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < cardCount; i++) {
            std::wstring card = L"Thẻ số " + std::to_wstring(i + 1);
            m_list->append(card);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto appendTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::wstring insertLine = L"Thêm: " + std::to_wstring(appendTime) + L" ms\n";
        result += insertLine;

        start = std::chrono::high_resolution_clock::now();
        Node* midCard = m_list->findByIndex(cardCount / 2);
        end = std::chrono::high_resolution_clock::now();
        auto findTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::wstring findLine = L"Tìm:  " + std::to_wstring(findTime) + L" μs\n";
        result += findLine;

        Node* firstCard = m_list->findByIndex(0);
        if (firstCard) {
            start = std::chrono::high_resolution_clock::now();
            m_list->deleteNode(firstCard->data);
            end = std::chrono::high_resolution_clock::now();
            auto deleteTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            std::wstring deleteLine = L"Xóa:  " + std::to_wstring(deleteTime) + L" μs\n";
            result += deleteLine;
        } else {
            result += L"Xóa:  N/A\n";
        }

        result += L"\n";
        result += L"Big-O:\n";
        result += L"Insert: O(1)\n";
        result += L"Find:   O(n)\n";
        result += L"Delete: O(1)\n";

        winrt::hstring hresult(result);
        TestResultText().Text(hresult);
        
        UpdateUI();

        std::wstring statusMsgStr;
        if (g_currentLanguage == AppLanguage::Vietnamese) {
            statusMsgStr = L"Đã hoàn tất test với " + std::to_wstring(cardCount) + L" thẻ";
        } else {
            statusMsgStr = L"Completed test with " + std::to_wstring(cardCount) + L" cards";
        }
        winrt::hstring statusMsg(statusMsgStr);
        ShowStatus(statusMsg, InfoBarSeverity::Success);
    }

    void FlashcardPage::Test10_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        TestPerformance(10);
    }

    void FlashcardPage::Test100_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        TestPerformance(100);
    }

    void FlashcardPage::Test1000_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        TestPerformance(1000);
    }

    void FlashcardPage::Test10000_Click([[maybe_unused]] winrt::Windows::Foundation::IInspectable const& sender, [[maybe_unused]] winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        TestPerformance(10000);
    }
}

