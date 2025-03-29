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

// struct flags fl;

bool renomme(std::string nom, std::string nouveauNom, std::string indent)
{
	
	if(fl.n_flag) {
		std::cout << indent << nom
		<< coul.FGVERT << " ==> Deviendrait ==> " << coul.RESET
		<< nouveauNom << '\n';
		return(false);
	}
	else {
		if (std::rename(nom.c_str(), nouveauNom.c_str())) {
			std::cout << coul.FGROUGE << "Je ne peux renommer "
				<< coul.RESET << nom << " en " << nouveauNom << std::endl;
			return(false);
		}
		if (fl.v_flag) std::cout << indent << nom
				<< coul.FGROUGE << " ==> est devenu ==> " << coul.RESET
				<< nouveauNom << '\n';
		return(true);
	}
}
