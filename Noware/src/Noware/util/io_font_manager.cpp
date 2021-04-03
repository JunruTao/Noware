#include "Noware/util/io_font_manager.h"
#include "Noware/util/system_helper.h"
#include "Noware/util/configure.h"

// Some typedefs to help simplify the field
typedef sf::String FKey;
typedef sf::Font Font;

//[Static MVar's] Init field
bool nw::FontManager::has_init = false;
std::map<FKey, Font> nw::FontManager::fonts;

//[Constructor]
nw::FontManager::FontManager() 
{
	if (!has_init)
	{
		nw::Util::DebugCallerConstructor("nw::FontManager");
		AddFont(DEFAULT_FONTNAME, DEFAULT_FONT_FILEPATH);
		has_init = true;
	}
}

//[Destructor]
nw::FontManager::~FontManager() 
{
    nw::Util::DebugCallerDestructor("nw::FontManager");
}

//[Add Font function] 
// pushing the fonts into a font map
void nw::FontManager::AddFont(FKey name, sf::String font_PATH) 
{
	if (fonts.find(name) != fonts.end())
	{
		std::cout
			<<"\n [nw::FontManager]: Font's name has exists in the library."
			<<"\n ------Double check the duplicates of [ " 
			<< std::string(name) 
			<< " ]\n -Status: [Font Not Loaded]"<<std::endl;
	}
	else 
	{
		std::cout 
			<< "\n [nw::FontManager]: -Loading Font: " 
			<< std::string(font_PATH) << " as " 
			<< std::string(name) << std::endl;

		sf::Font font;
		if (!font.loadFromFile(font_PATH))
		{
			throw std::runtime_error("[nw::FontManager] Failed to Load Font :" + std::string(font_PATH));
		}
		else
		{
			std::cout << "-Status: [Success] - continue=>>"<<std::endl;
			fonts.insert(std::pair<FKey, Font>(name, font));
		}
	}
}

//[MFunc Getter]
Font *nw::FontManager::GetFont(const FKey name)
{
	auto itr = fonts.find(name);
	if (itr != fonts.end())
		return &fonts[name];
	else
	{
		//TODO: can be improved
		// Note: This can be solver later as there are default font loaded, so that
		// this runtime error will be replaced by a warning call
		nw::Util::RuntimeError("[nw::FontManager] Font " + name + " not Found.");
	}
}

//[GLOBAL]
// The Global Instance of the font manager object
std::shared_ptr<nw::FontManager> nw::MasterFontManager = nullptr;