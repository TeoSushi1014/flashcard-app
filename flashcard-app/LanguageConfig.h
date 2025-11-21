#pragma once

enum class AppLanguage
{
    Vietnamese,
    English
};

// Biến global đơn giản
inline AppLanguage g_currentLanguage = AppLanguage::Vietnamese;

