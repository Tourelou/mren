#include <string>
#include <iostream>

#include "mren_locale.hpp"

std::string lang;

std::string get_lang_from_env() {
	const std::string testVariable[3] = {"LANG", "LC_ALL", "LANGUAGE"};
	
	for (const auto& var : testVariable) {
		const char* lang = std::getenv(var.c_str());
		if (lang == nullptr) continue;

		std::string langStr(lang); // Conversion en std::string
		langStr = langStr.substr(0, 2);
		return (langStr == "fr" || langStr == "en" || langStr == "es") ? langStr : "en"; 
	}
	return "en";
}

void set_mren_locale() {
	lang = get_lang_from_env();
}

std::string mren_locale(const std::string& key) {
	return translations.at(key).at(lang); // Utilise les traductions depuis `arc_locale.hpp`
}
