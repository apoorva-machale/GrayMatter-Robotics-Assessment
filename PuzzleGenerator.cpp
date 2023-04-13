#include "PuzzleGenerator.h"
using namespace std;

PuzzleGenerator::PuzzleGenerator(int _nRows, int _nColumns, int _minVal, int _maxVal)
	:nRows(_nRows), nColumns(_nColumns), minVal(_minVal), maxVal(_maxVal)
{}

Puzzle PuzzleGenerator::GeneratePuzzle()
{
	timer.StartTimer();
	maxtime = 59.9;	// To make sure we don't exceed a minute

	Puzzle bestPuzzleFound = RandomWalk(4);

	while (timer.GetElapsedTime() + 4 < maxtime) {
		Puzzle p = RandomWalk(4);
		if (p.GetValue() > bestPuzzleFound.GetValue()) {
			bestPuzzleFound = p;
		}
	}

	return bestPuzzleFound;
}

int PuzzleGenerator::GetValue(const Puzzle& puzzle) const {
    return const_cast<Puzzle&>(puzzle).GetValue();
}


Puzzle PuzzleGenerator::RandomWalk(double timelimit)
{
	// A very simple function that starts at a random configuration and keeps randomly modifying it
	// until the time limit is reached. Returns the best solution found so far.

	Puzzle p(nRows, nColumns, minVal, maxVal);	// Generate a random puzzle with the specified values.

	// Keep track of the best puzzle found so far (and its value).
	Puzzle bestPuzzle = p;
	int bestValue = p.GetValue();

	// Keep track of the time so we don't exceed it.
	Timer t;
	t.StartTimer();

	// Loop until we hit the time limit.
	//while (t.GetElapsedTime() < timelimit-0.1)	// To make sure that we don't exceed the time limit, we stop just before we hit the time limit.
	//{
		// Generate a successor of p by randomly changing the value of a random cell
		// (since we are doing a random walk, we just replace p with its successor).
	//	p = p.GetRandomSuccessor();

		// Update the current best solution.
	//	if (p.GetValue() > bestValue)	// Calling GetValue() for the first time is costly
										// since the puzzle has to be evaluated first.
	//	{
	//		bestValue = p.GetValue();	// Calling it a second time simply returns the value that was computed before.
	//		bestPuzzle = p;
	//	}
	//}

    while (t.GetElapsedTime() < timelimit-0.1) // To make sure that we don't exceed the time limit, we stop just before we hit the time limit.
    {
        vector<Puzzle> successors;
        bestPuzzle.GetAllSuccessors(successors);

        // Find the successor with the highest value.
        Puzzle bestSuccessor = p;
        int bestSuccessorValue = p.GetValue();
	for (vector<Puzzle>::iterator it = successors.begin(); it != successors.end(); ++it)
	{
    	    const Puzzle& successor = *it;
	    int successorValue = GetValue(successor);

            if (successorValue > bestSuccessorValue)
            {
                bestSuccessor = successor;
                bestSuccessorValue = successorValue;
            }
        }

        // If the best successor has a higher value than the current puzzle, update the current puzzle and bestPuzzle.
        if (bestSuccessorValue > bestValue)
        {
            p = bestSuccessor;
            bestValue = bestSuccessorValue;
            bestPuzzle = bestSuccessor;
        }
        else
        {
            // If there are no better successors, return the best puzzle found so far.
            return bestPuzzle;
        }
    }

    

	return bestPuzzle;

	// The following code is not executed in this function. It exists just as an example for getting all the successors of a puzzle.
	//vector<Puzzle> successors;
	//bestPuzzle.GetAllSuccessors(successors);
}
