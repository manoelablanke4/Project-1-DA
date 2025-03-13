#ifndef MENU_H
#define MENU_H

#include "../include/IndependentRoutePlanning.h"
#include "../include/RestrictedRoutePlanning.h"
#include "../include/data_structures/Graph.h"

void handleMenuSelection();
void planFastestRoute(int origin, int destination, bool altPath);

#endif // MENU_H
