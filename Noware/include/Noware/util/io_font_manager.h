#ifndef _IO_FONT_MANAGER_H_
#define _IO_FONT_MANAGER_H_
#include "Noware/util/externals.h"
#include "Noware/util/macro_field.h"


namespace nw
{
    class FontManager
    {
        typedef sf::String FKey;
        typedef sf::Font Font;

    public:
        FontManager();
        ~FontManager();
        void AddFont(FKey name, sf::String font_PATH);
        Font *GetFont(const FKey name);

    private:
        static bool has_init;
        static std::map<FKey, Font> fonts;
    };

    _GLOBAL_ std::shared_ptr<FontManager> MasterFontManager;
}

#endif