#include <iostream>
#include <unistd.h> // chdir(), getcwd(), rename()

#ifdef __linux__
		#include <linux/limits.h>
#endif

#include "global.h"

std::string get_working_path()
{
	char pathBuf[PATH_MAX];

	if (getcwd(pathBuf, PATH_MAX) == 0) {

		int error = errno;

		switch (error) {
			// EINVAL can't happen - size argument > 0

			// PATH_MAX includes the terminating nul, 
			// so ERANGE should not be returned

			case EACCES:
				std::cout << "Access denied" << std::endl;

			case ENOMEM:
				// I'm not sure whether this can happen or not 
				std::cout << "Insufficient storage" << std::endl;

			default: {
				std::cout << "Unrecognised error" << std::endl;
			}
		}
	}
	return std::string(pathBuf);
}


const std::string fr_devient = " " + coul.FGVERT +
									" ==> Deviendrait ==> " +
										coul.RESET + " ";
const std::string en_devient = " " + coul.FGVERT +
									" ==> would become ==> " +
										coul.RESET + " ";
std::string devient;
const std::string fr_devenu = " " + coul.FGROUGE +
									" ==> est devenu ==> " +
										coul.RESET + " ";
const std::string en_devenu = " " + coul.FGROUGE +
									" ==> became ==> " +
										coul.RESET + " ";
std::string devenu;

void setRenommeLocale() {
	if (langFranc) {
		devient = fr_devient;
		devenu = fr_devenu;
	}
	else {
		devient = en_devient;
		devenu = en_devenu;
	}
}

bool renomme(std::string nom, std::string nouveauNom, std::string indent)
{
	if(fl.n_flag) { std::cout << indent << nom << devient << nouveauNom << '\n';
		return(false);
	}
	else {
		if (std::rename(nom.c_str(), nouveauNom.c_str())) {
			if (langFranc) {
				std::cout << coul.FGROUGE << " Je ne peux renommer "
					<< coul.RESET << " " << nom << " en " << nouveauNom << std::endl;
			}
			else {
				std::cout << coul.FGROUGE << " Can't rename "
					<< coul.RESET << " " << nom << " to " << nouveauNom << std::endl;
			}
			return(false);
		}
		if (fl.v_flag) { std::cout << indent << nom << devenu << nouveauNom << '\n';
		}
		return(true);
	}
}
