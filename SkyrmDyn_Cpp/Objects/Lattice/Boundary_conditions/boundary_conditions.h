#ifndef BOUNDARY_CONDITIONS_H
#define BOUNDARY_CONDITIONS_H

#include "Objects/Cell/cell.h"
#include "Objects/Parameter/parameter.h"

bool test_neighboring_cells( Cell& cell1, Cell& cell2, Parameter parameters );

#endif // BOUNDARY_CONDITIONS_H
