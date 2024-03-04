#include "Header.hpp"


// Purpose: Gets next ticket from file
// Accepts: An ifstream associated with the file (passed by reference)
// Returns: A vector<int> holding the next ticket
std::vector<int> getNextSeries(std::ifstream& dataFile)
{
    // Declare a vector<int> to hold the winning ticket
    std::vector<int> ticketNumbers;

    // Get the next ticket from the file as a string
    std::string unparsedTicketNumbers;
    getline(dataFile, unparsedTicketNumbers);

    // Set up a stringstream for splitting the string at the "," delimiter
    std::istringstream ticketNumbersStream(unparsedTicketNumbers);

    // token to hold the number (as a string) and number to hold the number as an int
    std::string token;
    int number;

    // Parse each integer into a token from the ticket string, delimited by the commas
    while (getline(ticketNumbersStream, token, ',')) {
        // turn each token into an int
        number = std::atoi(token.c_str());
        // add the integer to the vector holding the current ticket number
        ticketNumbers.push_back(number);
    }
    return ticketNumbers;
}

// Purpose: Counts number of matching numbers between two tickets
// Accepts: Two vector<int>s holding the two tickets
// Returns: An integer, number of matching numbers
int countMatchingNumbers(std::vector<int> currentTicket, std::vector<int> winningTicket)
{
    int matchCount = 0;
    for (int i = 0; i < winningTicket.size(); i++)
    {
        for (int j = 0; j < currentTicket.size(); j++)
        {
            if (winningTicket[i] == currentTicket[j])
            {
                matchCount++;
            }
        }
    }
    return matchCount;
}

// Purpose: Formats a vector<int> holding the tickets into a string delimited by commas
// Accepts: A vector<int> holding the ticket numbers
// Returns: A string holding the formatted ticket
std::string formatTicketNumbers(std::vector<int> ticketNumbers)
{
    std::string formattedTicket = "";

    for (int i = 0; i < ticketNumbers.size(); i++)
    {
        formattedTicket += std::to_string(ticketNumbers[i]);
        if (i < ticketNumbers.size() - 1)
        {
            formattedTicket += ", ";
        }
    }
    return formattedTicket;
}

// Purpose: Prints a list of tickets in two columns
// Accepts: A 2D vector holding the list of tickets (vector<vector<int>>)
// Returns: Void 
void printTickets(std::vector<std::vector<int>> ticketList)
{
    // print header for the first line
    printf("%-20s ", "Ticket numbers:");

    for (int i = 0; i < ticketList.size(); i++)
    {
        // Print a new line and a leading space every two tickets except for the first row
        if (i > 0 && i % 2 == 0)
        {
            printf("\n");
            printf("%-20s ", "");
        }

        // Change the spacing of the columns based on the length of the tickets
        if (ticketList[i].size() < 5)
        {
            printf("%-25s", formatTicketNumbers(ticketList[i]).c_str());
        }
        else if (ticketList[i].size() < 8)
        {
            printf("%-30s", formatTicketNumbers(ticketList[i]).c_str());
        }
        else if (ticketList[i].size() <= 10)
        {
            printf("%-45s", formatTicketNumbers(ticketList[i]).c_str());
        }
    }
    printf("\n\n");
}

