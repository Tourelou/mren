#include <string>
#include <cstdlib>	// std::getenv()
#include <algorithm> // std::transform()

bool getFrancais() {
	const std::string testVariable[3] = {"LANG", "LC_ALL", "LANGUAGE"};
	
	for (const auto& var : testVariable) {
		const char* lang = std::getenv(var.c_str());
		if (lang == nullptr) continue;

		std::string langStr(lang); // Conversion en std::string
		std::transform(langStr.begin(), langStr.end(), langStr.begin(), ::tolower);

		if (langStr.find("fr") != std::string::npos) {
			return true;
		}
	}
	return false;
}
