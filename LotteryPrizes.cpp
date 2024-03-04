#include "Header.hpp"

int main() 
{
    // Constants
    const int LOTTERY_MINIMUM = 1000;

    // File Header
    std::cout << "Lottery Prizes Analyzer" << std::endl << std::endl;

    // User input
    // Prompt the user for the name of the lottery
    std::cout << "Enter the name of the lottery: ";
    std::string lotteryName;
    std::getline(std::cin, lotteryName);

    // Prompts the user for the total amount in prize pool, validates for an amount over $1000
    std::cout << std::endl << "Enter the amount of money in the prize pool: ";
    int prizePoolTotal;
    std::cin >> prizePoolTotal;
    while (prizePoolTotal < LOTTERY_MINIMUM) 
    {
        std::cout << "Invalid entry. please enter an amount that is greater or equal to " << LOTTERY_MINIMUM << ": ";

        std::cin >> prizePoolTotal;
    }

    // Declare constants for each prize total
    const double GRAND_PRIZE_PORTION = 0.85;
    const double SECOND_PRIZE_PORTION = 0.07;
    const double THIRD_PRIZE_PORTION = 0.08;
    
    const double GRAND_PRIZE = GRAND_PRIZE_PORTION * prizePoolTotal;
    const double SECOND_PRIZE = SECOND_PRIZE_PORTION * prizePoolTotal;
    const double THIRD_PRIZE = THIRD_PRIZE_PORTION * prizePoolTotal;

    // Prompts the user for the file path of the file containing all of the ticket numbers
    std::cout << std::endl << "Enter the path for the data file: ";
    std::string filePath;
    std::cin >> filePath;

    // Setting up the file 
    std::ifstream dataFile;
    
    // Open the file, print an error message if it doesn't open
    dataFile.open(filePath);

    if (dataFile.fail()) {
        std::cerr << "Unable to open the file " << filePath << std::endl;
        return 1;
    }

    // Declare an int vector to hold the next ticket
    std::vector<int> winningTicket = getNextSeries(dataFile);

    // Declare constant variable to hold ticket length
    const int TICKET_LENGTH = winningTicket.size();
    
    // Declare counter variables for winners
    int totalTicketCount = 0;
    int grandWinnerCount = 0;
    int secondWinnerCount = 0;
    int thirdWinnerCount = 0;

    // Declare two 2D vectors to hold the second and third place winners
    std::vector<std::vector<int>> secondPlaceWinners;
    std::vector<std::vector<int>> thirdPlaceWinners;

    // Loop to read from file ticket by ticket
    while (dataFile.peek() != EOF) 
    {
        // Get the next ticket from file
        std::vector<int> currentTicket = getNextSeries(dataFile);

        // Get the current number of matches 
        int matchCount = countMatchingNumbers(currentTicket, winningTicket);

        // Assign the winners and increment corresponding count and winner list
        if (matchCount == TICKET_LENGTH)
        {
            grandWinnerCount++;
        }
        else if (matchCount == TICKET_LENGTH - 1)
        {
            secondWinnerCount++;
            secondPlaceWinners.push_back(currentTicket);
        }
        else if (matchCount == TICKET_LENGTH - 2)
        {
            thirdWinnerCount++;
            thirdPlaceWinners.push_back(currentTicket);
        }
        // Increment total ticket counter
        totalTicketCount++;

    }// end of file reading loop

    // Calculate prize amount for each winner, ensure no division by zero if zero winners
    double grandPrizeSplit;
    if (grandWinnerCount == 0)
    {
        grandPrizeSplit = 0;
    }
    else
    {
        grandPrizeSplit = GRAND_PRIZE / grandWinnerCount;
    }

    double secondPrizeSplit;
    if (secondWinnerCount == 0)
    {
        secondPrizeSplit = 0;
    }
    else
    {
        secondPrizeSplit = SECOND_PRIZE / secondWinnerCount;
    }

    double thirdPrizeSplit;
    if (thirdWinnerCount == 0)
    {
        thirdPrizeSplit = 0;
    }
    else 
    {
        thirdPrizeSplit = THIRD_PRIZE / thirdWinnerCount;
    }

    // Final report output
    printf("\nLottery Prize Report");
    printf("\n---------------------\n\n");

    // General information report
    printf("%-20s %s\n", "Lottery Name:", lotteryName.c_str());
    printf("%-20s $%d\n", "Total prize pool:", prizePoolTotal);
    printf("%-20s %i\n", "Number of tickets:", totalTicketCount);
    printf("%-20s %s\n\n", "Winning numbers:", formatTicketNumbers(winningTicket).c_str());

    // Grand prize winner report
    printf("Grand prize winners (all numbers match)...\n");
    printf("%-20s %i\n", "Number of winners:", grandWinnerCount);
    printf("%-20s %.1f\n", "% of prize pool:", GRAND_PRIZE_PORTION * 100);
    printf("%-20s $%.2f\n", "Total prize value:", GRAND_PRIZE);
    printf("%-20s $%.2f\n\n", "Prize per ticket", grandPrizeSplit);

    // Second prize winner report
    printf("Second prize winners (%i numbers match)...\n", TICKET_LENGTH - 1);
    printf("%-20s %i\n", "Number of winners:", secondWinnerCount);
    printf("%-20s %.1f\n", "% of prize pool:", SECOND_PRIZE_PORTION * 100);
    printf("%-20s $%.2f\n", "Total prize value:", SECOND_PRIZE);
    printf("%-20s $%.2f\n", "Prize per ticket", secondPrizeSplit);
    printTickets(secondPlaceWinners);

    // Third prize winner report
    printf("Second prize winners (%i numbers match)...\n", TICKET_LENGTH - 2);
    printf("%-20s %i\n", "Number of winners:", thirdWinnerCount);
    printf("%-20s %.1f\n", "% of prize pool:", THIRD_PRIZE_PORTION * 100);
    printf("%-20s $%.2f\n", "Total prize value:", THIRD_PRIZE);
    printf("%-20s $%.2f\n", "Prize per ticket", thirdPrizeSplit);
    printTickets(thirdPlaceWinners);

    // close file
    dataFile.close();
}


