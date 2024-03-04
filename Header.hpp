#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>


// Function headers
std::vector<int> getNextSeries(std::ifstream& dataFile);
int countMatchingNumbers(std::vector<int> currentTicket, std::vector<int> winningTicket);
std::string formatTicketNumbers(std::vector<int> ticketNumbers);
void printTickets(std::vector<std::vector<int>> ticketList);
