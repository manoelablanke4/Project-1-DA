#ifndef MENU_H
#define MENU_H

/**
 * @file Menu.h
 * @brief Function declarations related to user menu interaction and route planning options.
 */

#include "../include/IndependentRoutePlanning.h"
#include "../include/RestrictedRoutePlanning.h"
#include "../include/data_structures/Graph.h"

/**
 * @brief Starts the interactive menu loop, allowing the user to select route planning options.
 * @note **Time Complexity:** O((N + M) log N), governed by route-planning algorithms.
 */
void handleMenuSelection();

/**
 * @brief Handles manual input to compute the fastest route.
 *
 * @note **Time Complexity:** O((N + M) log N), due to internal Dijkstra algorithm calls.
 */
void planFastestRouteMenu();

/**
 * @brief Handles batch mode input from files to compute fastest routes.
 *
 * @note **Time Complexity:** O(L + (N + M) log N), L is input file lines.
 */
void planFastestRouteBatch();

#endif // MENU_H
