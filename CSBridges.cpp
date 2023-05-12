#include "CSBridges.h"
#include "Lawn/Plant.h"

PlantDefinition& GlobalPlantDefinitions::operator[](int index)
{
		return Functions::gPlantDefinition(index);
}
