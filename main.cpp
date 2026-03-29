#include <iostream>
#include <string>
#include "HashMap.h"
#include "Trie.h"
using namespace std;

// Helper function to handle user choices.
string getPlayerChoice(char maxChoice) {
    string user_choice;
    maxChoice = toupper(maxChoice);  // Allows for varying number of choices.

    // Use a while loop for input validation.
    while (true) {
        cout << "Enter your choice (A to " << maxChoice << "): ";
        cin >> user_choice;

        // Check 1: Ensure length of user_choice is exactly one character long.
        if (user_choice.length() != 1) {
            cout << "Invalid input. Please type a single letter choice." << endl;
            continue;
        }

        // Check 2: Ensure uppercase.
        char choiceLetter = toupper(user_choice[0]);

        // Check 3: Ensure choice is within bounds.
        if (choiceLetter >= 'A' && choiceLetter <= maxChoice) {
            // Convert the char to a string.
            return string(1, choiceLetter);
        }

        cout << "Invalid choice! Please choose a letter between A and " << maxChoice << "." << endl;
    }
}

// Helper function to generate ONE random choice.
string getRandomChoice(int numOptions) {
    // Get a random number between 0 and (numOptions - 1)
    int randomNumber = rand() % numOptions;

    // Shift it to a character (Ex: 'A' + 0 would be 'A' and 'A' + 1 would be 'B', etc.)
    char randomChoice = 'A' + randomNumber;

    return string(1, randomChoice);
}

// Function to generate random players.
void generateRandomPlayers(HashMap& hashDatabase, Trie& trieDatabase, int numPlayers) {
    for (int i = 1; i <= numPlayers; ++i) {
        string currentPath = "";

        // Scene 1
        string s1 = getRandomChoice(3);
        currentPath += s1;
        if (currentPath == "C") {
            hashDatabase.insertDecisionPath(currentPath);
            trieDatabase.insertDecisionPath(currentPath);
            continue;
        }

        // Scene 2
        string s2 = getRandomChoice(2);
        currentPath += s2;

        // Scene 3
        currentPath += getRandomChoice(2);
        if (currentPath == "AAA" || currentPath == "ABB" || currentPath == "BAA" || currentPath == "BAB" || currentPath == "BBB") {
            hashDatabase.insertDecisionPath(currentPath);
            trieDatabase.insertDecisionPath(currentPath);
            continue;
        }

        // Scene 4
        currentPath += getRandomChoice(2);
        if (currentPath == "AABA" || currentPath == "ABAA" || currentPath == "ABAB" || currentPath == "BBAB") {
            hashDatabase.insertDecisionPath(currentPath);
            trieDatabase.insertDecisionPath(currentPath);
            continue;
        }

        // Scene 5
        currentPath += getRandomChoice(2);
        if (currentPath == "AABBA" || currentPath == "AABBB" || currentPath == "BBAAA" || currentPath == "BBAAB") {
            hashDatabase.insertDecisionPath(currentPath);
            trieDatabase.insertDecisionPath(currentPath);
            continue;
        }

        // 3. Insert into both
        hashDatabase.insertDecisionPath(currentPath);
        trieDatabase.insertDecisionPath(currentPath);
    }
}

// Helper function to generate an end sequence.
void gameEndSequence(HashMap& hashDatabase, Trie& trieDatabase, string playerPath) {
    hashDatabase.insertDecisionPath(playerPath);
    trieDatabase.insertDecisionPath(playerPath);
    
    cout << "Your choice path was: " << playerPath << endl;
    cout << "Here's what other players chose to do: " << endl;
    
    cout << "\n[HashMap Stats]:";
    hashDatabase.printPerChoiceStatistics(playerPath);

    cout << "\n[Trie Stats]:";
    trieDatabase.printPerChoiceStatistics(playerPath);

    cout << "\n\n THANKS FOR PLAYING";
}

int main() {
    // 1. Initialize your custom HashMap and Trie
    HashMap hashGameStats(1000);
    Trie trieGameStats;

    // 2. Generate 10 random players
    generateRandomPlayers(hashGameStats, trieGameStats, 10);

    // 3. Initialize user current path and choice variables.
    string userCurrentPath = "";
    string choice1, choice2, choice3, choice4, choice5;

    // Scene 1
    cout << "Chapter 1" << endl;
    cout << "You wake up on the ground. Cold floor, low light, no memory of how you got here. There's a sound somewhere ahead, it's faint... maybe human? The corridor behind you has already sealed shut. You checked. Twice. Three passages open in front of you. Somewhere in this place is a way out... you just have to find it. Pick a road. You're good at that." << endl << endl;
    cout << "Options" << endl;
    cout << "A: Left\nB: Middle\nC: Right\nChoice: ";
    cin >> choice1;
    userCurrentPath.append(choice1);

    // Path: A
    if (choice1 == "A") {
        cout << "Chapter 2" << endl;
        cout << "The left passage is narrower than it looked. A lot narrower. You turn sideways to fit, which is fine. This is fine.\nThere's a light ahead. Moving. Someone carrying it, walking away from you. Getting smaller.\nYou almost call out.\nThen you stop.\nTo the right: a cracked door. Light coming through the gap at the bottom. Not this-place light.\nReal light. Outside light.\nYour heart does something embarrassing.\nThe person with the light is almost gone. You have maybe ten seconds." << endl << endl;
        cout << "Options" << endl;
        cout << "A: call out to them\nB: go through the door\nChoice: ";
        cin >> choice2;
        userCurrentPath.append(choice2);

        // Path: AA
        if (choice2 == "A") {
            cout << "Chapter 3" << endl;
            cout << "They stop.\nYou know them. Not dramatically. Just... you know them. The kind of person who faded out of your life slowly, the way those things go. You kept choosing other things. Then one day they just weren't there anymore.\nAnd now they are here.\nThey don't look surprised. That's the part that gets you.\n\"Been in here a while,\" they say. \"Mapped most of it.\"\nThey hold up the light. The battery indicator is blinking red.\nEvery junction in this place splits exactly twice, they say. Not once. Not three times. Always two. Like a system. Like someone designed this on purpose and then put people in it and called it a maze.\nThey think they found a way out. The passage ahead is new ground. They've been working up to it for a while.\nThe light flickers." << endl << endl;
            cout << "Options" << endl;
            cout << "A: \"Let's go. Right now.\"\nB: \"Wait. How long have you actually been in here?\"\nChoice: ";
            cin >> choice3;
            userCurrentPath.append(choice3);

            // Path: AAA
            if (choice3 == "A") {
                cout << "Chapter 4" << endl;
                cout << "You go.\nFast. The passage twists left, then right. You can feel something like hope, which you haven't had since you woke up on that cold floor. That's probably a bad sign.\nDead end.\nSolid wall. No marks. No door. Nothing.\nYou put your hand against it.\nIt doesn't move. It was never going to.\nBehind you, somewhere in the dark, you can still hear them. Still moving. Still looking.\n...\n...\nYou chose the road. You just never checked where it went." << endl << endl;
                cout << "\tGAME OVER" << endl << endl;
                gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
            }

            // Path: AAB
            else if (choice3 == "B") {
                cout << "Chapter 4" << endl;
                cout << "They think about it.\n\"Long enough to know the layout.\" A pause. \"Long enough to stop counting.\"\nYou walk beside them. For a while it almost feels normal. Like you're just going somewhere together the way you used to, before you kept choosing other things.\nThe light flickers. Longer this time.\nEvery junction in this place splits exactly twice. No exceptions. Someone built this. Someone designed a system, filled it with people, sealed the exits, and left.\nThe mapped sections end in twenty meters.\n\"One of us should go first,\" they say. \"Past this point, I don't know what's there.\"\nThe light blinks." << endl << endl;
                cout << "Options" << endl;
                cout << "A: you go first. You've been waiting long enough.\nB: let them lead. They know this place. You don't.\nChoice: ";
                cin >> choice4;
                userCurrentPath.append(choice4);

                // Path: AABA
                if (choice4 == "A") {
                    cout << "Chapter 5" << endl;
                    cout << "You step ahead.\nThe passage curves. Then forks. You take left.\nDead end.\nDifferent kind, though. There's writing on the wall. Hundreds of scratches. Names maybe. Dates. Someone was here a long time before you, marking every turn, recording every dead end, leaving something behind just to prove they'd been there.\nYou find a blank space and scratch in your initials.\nSmall. But something.\nThe passage doesn't open. But sitting down against the wall, you don't feel trapped the same way anymore.\nYou wait.\n...\nThe road less traveled had no guarantee. But you went anyway. That's the part worth keeping.";
                    gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
                }

                // Path: AABB
                else if (choice4 == "B") {
                    cout << "Chapter 5" << endl;
                    cout << "They move fast now. Confident. The mapped sections fall away behind you, one junction at a time.\nThen they slow.\nOne final fork. Two passages. Perfectly symmetrical. No marks. No hints. Nothing to go on at all.\n\"I've never been past here,\" they say quietly. \"I always turned back.\"\nThey look at you. The light is almost gone.\nThis is the place they couldn't get through alone." << endl << endl;
                    cout << "Options" << endl;
                    cout << "A: left. You have a feeling. You've learned to trust those.\nB: right. Let them decide this one. You've been guessing long enough.\nChoice: ";
                    cin >> choice5;
                    userCurrentPath.append(choice5);

                    // Path: AABBA
                    if (choice5 == "A") {
                        cout << "Chapter 6" << endl;
                        cout << "Left.\nThe passage opens.\nJust like that. Like the maze got tired. Like it was always going to end here and was just waiting for you to show up.\nThere's a door at the end. Real light around every edge. You push it and the air hits you first. Warm. Different. Outside.\nYou look back. They're still standing at the fork.\nYou could call to them. You could wait.\nYou don't know if they'll follow.\nThe door is open. You found it.\n...\nTwo roads diverged. You took the one that felt right. This time, for once, it was." << endl;
                        gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
                    }

                    // Path: AABBB
                    else if (choice5 == "B") {
                        cout << "Chapter 6" << endl;
                        cout << "They choose right.\nThe passage runs long. Longer than it should. It curves back and keeps going and you start to wonder if you made a mistake.\nThen it opens into a small chamber.\nHigh on the wall: a window. Way too small to climb through. But sunlight is coming through it. Real sunlight. You can feel the warmth from here.\nYou both just stand there.\n\"There's a way out,\" they say quietly. \"We just haven't found it yet.\"\nYou nod.\nFor the first time since you woke up on that cold floor, not yet feels like enough.\n...\nYou knew, before you'd taken a single step, which road you'd end up on. But the road taught you something anyway." << endl;
                        gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
                    }
                }
            }
        }

        // Path: AB
        else if (choice2 == "B") {
            cout << "Chapter 3" << endl;
            cout << "The door opens into a room.\nOne way in. One way out: a door at the far end, light coming through the gap at the bottom.\nReal light. Outside light. It is right there.\nYou try the handle.\nThe handle is on the other side.\nOf course it is.\nYou can see it through the gap. It's just sitting there, completely reachable, completely useless to you from this side. You could fit something thin under the door, hook it, pull it toward you. Maybe. Probably.\nBehind you, faint, you can still hear the other person. Getting further away." << endl << endl;
            cout << "Options" << endl;
            cout << "A: you can get this open. You just need something thin enough.\nB: go back. You need help with this one.\nChoice: ";
            cin >> choice3;
            userCurrentPath.append(choice3);

            // Path: ABA
            if (choice3 == "A") {
                cout << "Chapter 4" << endl;
                cout << "There's a wire bracket on the wall. Loose. You work it free. Thirty seconds of swearing under your breath.\nYou thread it through the gap.\nThe handle catches.\nThe door moves.\nOne inch.\nTwo inches.\nSomething wedged on the other side. But you can feel the air already. Warm. Real. Pouring through that gap like it has been waiting for you specifically.\nTwo inches of outside.";
                cout << "Options" << endl;
                cout << "A: push harder. You are not stopping this close.\nB: step back. Two inches is not enough. There has to be another way.\nChoice: ";
                cin >> choice4;
                userCurrentPath.append(choice4);

                // Path: ABAA
                if (choice4 == "A") {
                    cout << "Chapter 5" << endl;
                    cout << "You push.\nThree inches. Four. Warm air coming through steady now, real and close.\nThe wire slips.\nThe handle releases.\nThe door closes. Not slammed. Quietly. Gently. Like it was never really open for you. Like the whole thing was already decided before you picked up that wire.\nYou stand there for a while.\n...\n...\nYou took the road less traveled. Someone, somewhere, is taking the other one right now. Still hoping.";
                    cout << "\tGAME OVER" << endl << endl;
                    gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
                }

                // Path: ABAB
                else if (choice4 == "B") {
                    cout << "Chapter 5" << endl;
                    cout << "You step back.\nTwo inches isn't enough. You know the difference between almost and there.\nYou leave the room. Walk deeper in. Deliberately this time. Not panicking. Just moving.\nLeft branch. Right branch. Another left.\nThere's a door at the end of a passage you almost walked past entirely.\nIt opens from your side.\n...\nThe road you took because you had no other options turned out to be the one that went somewhere.";
                    gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
                }
            }

            // Path: ABB
            else if (choice3 == "B") {
                cout << "Chapter 4" << endl;
                cout << "You go back.\nThe light is already smaller.\nYou pick up the pace.\nIt gets smaller faster than it should.\nYou call out.\nNothing.\nThe light disappears.\nYou stand there after. Long enough to know it's not coming back. Long enough to understand that knowing doesn't actually change anything.\nEventually you turn and walk back into the dark.\n...\n...\nTwo roads diverged. You stood at the fork so long deciding, the road you finally chose had already moved on without you.";
                cout << "\tGAME OVER" << endl << endl;
                gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
            }
        }
    }

    // Path: B
    else if (choice1 == "B") {
        cout << "Chapter 2" << endl;
        cout << "You head towards the middle passage. It's a bit of an awkward fit. As you go further in, you notice that the ceiling appears closer than before. Looking back, you can see that it's been angling downwards ever so slightly since the beginning. There's no point in turning back now, so you continue forwards. By the time you reach the end of the hallway, you are crawling on all fours. There's a torch at the end. You see stairs downwards to the left, and to the right you see just a longer, narrow crawlspace." << endl << endl;
        cout << "Options" << endl;
        cout << "A: you go left, down the stairs\nB: you go right, into the crawlspace\nChoice: ";
        cin >> choice2;
        userCurrentPath.append(choice2);

        // Path: BA
        if (choice2 == "A") {
            cout << "Chapter 3" << endl;
            cout << "Going towards the stairs is obviously the right choice. You'll have more space as the stairs descend and the ceiling stays the same. No more crawling! You head left and after just a bit more crawling, you are able to stand upright again. You walk down the stairs.\n...\n...\n...\nMan, it sure is a long way down.\n...\n...\n...\nYou wonder where these stairs are heading.\n...\n...\n...\nThese stairs do head somewhere right?\n...\n...\n...\nYou've walked a long way. You can't turn back now.\n...\n...\n...\nYou look up. You don't see a ceiling. Y-You can't see anything there. It's just darkness. You look back up the stairs. There's nothing there. Not even the light from the torch at the crossroads. Maybe you should turn back? It's not too late, right?" << endl << endl;
            cout << "Options" << endl;
            cout << "A: go back up the stairs\nB: continue down the stairs\nChoice: ";
            cin >> choice3;
            userCurrentPath.append(choice3);

            // Path: BAA
            if (choice3 == "A") {
                cout << "Chapter 4" << endl;
                cout << "You have to head back. Sure you've come down a long way, but there's still time to turn back. There's still time. You turn around and take a step forward. Your foot touches nothing. The stair isn't there. You're falling.\n...\n...\n...\nFalling.\n...\n...\n...\nFalling.\n...\n...\n...\nMore falling.\n...\n...\n...\nEven more falling.\n...\n...\n...\nOh what's that? You're still falling? Great.\n...\n...\n...\nWhat a thrilling adventure.\n...\n...\n...\nYou're still falling.\n...\n...\n...\nThis is fine.\n...\n...\n...\nThis is it, isn't it?\n...\n...\n...\nYeah. This is it." << endl;
                cout << "\tGAME OVER" << endl << endl;
                gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
            }

            // Path: BAB
            else if (choice3 == "B") {
                cout << "Chapter 4" << endl;
                cout << "You've come all this way. You can't turn back now. You just can't. You have to go on. There's no way you can stop now. You're too deep into this. You go down the stairs.\n...\n...\n...\nDown the stairs.\n...\n...\n...\nDown the stairs.\n...\n...\n...\nDown more stairs.\n...\n...\n...\nDown even more stairs.\n...\n...\n...\nThere's... still more stairs.\n...\n...\n...\nTh-There has to be an end to this right?\n...\n...\n...\nThis can't be all there is.\n...\n...\n...\nThere can't be more stairs. There shouldn't be more stairs.\n...\n...\n...\nMORE STAIRS\n...\n...\n...\nWHY MORE STAIRS\n...\n...\n...\nIT'S NOT FAIR\n...\n...\n...\nThis is it, isn't it?\n...\n...\n...\nYeah. This is it." << endl;
                cout << "\tGAME OVER" << endl << endl;
                gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
            }
        }

        // Path: BB
        else if (choice2 == "B") {
            cout << "Chapter 3" << endl;
            cout << "You're not sure if the stairs are a good idea. They're going downwards. That can't possibly be good. Yeah. That makes sense. Down is bad. Up is good. The crawlspace isn't exactly up, but it's better than down. You crawl towards the right. After while, you notice that the crawlspace seems to have gotten... smaller. Tighter. That's... That's fine. For now. Yeah, that's fine for now. That's fine, right? Right? RIGHT?!?" << endl << endl;
            cout << "Options" << endl;
            cout << "you rush forward\nB: you take a minute to calm down\nChoice: ";
            cin >> choice3;
            userCurrentPath.append(choice3);

            // Path: BBA
            if (choice3 == "A") {
                cout << "Chapter 4" << endl;
                cout << "You can't take a break now. You don't know how long you've been here, but you know you need to get out as soon as possible. You start crawling faster through the crawlspace. You can still feel your heart racing as you push through and the space continues to get smaller. You need to hurry. Faster, and faster, and faster, and faSTER, AND FASTER, AND FASTER, AND THERE!\nYou see a light in the distance, coming out of a... ventilation shaft? You crawl towards it faster. As you get closer, you notice an opening in the ceiling. The space above is wider than the crawlspace, and you see rungs to climb upwards." << endl << endl;
                cout << "Options" << endl;
                cout << "A: you head towards the light\nB: you head up the ladder\nChoice: ";
                cin >> choice4;
                userCurrentPath.append(choice4);

                // Path: BBAA
                if (choice4 == "A") {
                    cout << "Chapter 5" << endl;
                    cout << "You decide to head towards the light. You've struggled all this way, and the end is clearly in sight. You crawl forwards for just a bit more and reach the vent. It's old and rustly, clearly worn out for one reason or the other. You try to peek through it to see what's on the other side, but can't see anything due to the light. You push against the vent with all your strength and it breaks. The light is almost blinding after being in the dark for so long. You close your eyes and squeeze through the vent, and as you crawl out you can feel grass and the heat of the sun on your face. Slowly, your adjust to the light and you can see a flat field of grass and the occasional tree ahead of you." << endl << endl;
                    cout << "Options" << endl;
                    cout << "A: you run ahead and don't look back\nB: you look back before running ahead\nChoice: ";
                    cin >> choice5;
                    userCurrentPath.append(choice5);

                    // Path: BBAAA
                    if (choice5 == "A") {
                        cout << "Chapter 6" << endl;
                        cout << "You run ahead as fast as you can and don't look back. Whatever that place was, how you got there, it doesn't matter to you. You don't want to know. You just want to be free. You run and run and run until you're gasping for air and fall to your knees. You breathe in and out heavily, but unlike the cramped crawlspace, you feel like you can actually still breathe. It's a relief. It's such a relief to get away. You don't think about that place anymore. Whatever it was. You take a moment to gather your bearings, and then you continue to run away.\nYou're free." << endl;
                        cout << "\tYOU ESCAPED" << endl << endl;
                        gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
                     }

                    // Path: BBAAB
                    else if (choice5 == "B") {
                        cout << "Chapter 6" << endl;
                        cout << "You turn around to see what you escaped. The building behind you is tall and black. It looks so out of place in your natural surroundings. Seeing its never-ending height makes you gasp out in disbelief. How is this possible? What is this place? Yet as you continue to look at it, you realize that it doesn't really matter. You look at the building that gave you such terror, and reflect upon the decision you made, think about the choices you didn't make, ponder about what could have been. You are content with where you are and calm against what you have faced. You turn back around and slowly, but surely, move forward. Each step you take is strengthened and calm and filled with purpose.\nYou're free." << endl;
                        cout << "\tYOU ESCAPED" << endl << endl;
                        gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
                    }
                }

                // Path: BBAB
                else if (choice4 == "B") {
                    cout << "Chapter 5" << endl;
                    cout << "You decide to go up the rungs. Finally, you can stand and are less cramped than before. You take a moment to catch your breath. Then, you start climbing up.\n...\n...\n...\nUp the rungs.\n...\n...\n...\nUp the rungs.\n...\n...\n...\nUp the rungs.\n...\n...\n...\nUp even more rungs.\n...\n...\n...\nThere's... still more rungs.\n...\n...\n...\nTh-There has to be an end to this right?\n...\n...\n...\nThis can't be all there is.\n...\n...\n...\nThere can't be more rungs. There shouldn't be more rungs.\n...\n...\n...\nThe exhaustion gets to you. It's too much. You can't do much more. You took a large risk. You thought you could have it all. You thought you could go up. UP, of all things. Your limbs are exhausted. There's only one way to go from here.\nDown." << endl;
                    cout << "\tGAME OVER" << endl << endl;
                    gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
                }
            }

            // Path: BBB
            else if (choice3 == "B") {
                cout << "Chapter 4" << endl;
                cout << "You take a minute to breathe. You can't freak out. It's too tight. You have to be rational. You can't breathe. You MUST calm down. IT'S TOO TIGHT You really should calm down. Deep breath in. Deep breath out. Again. It's fine. Everything is fine. You're okay. Deep breath in. Deep breath out. Again. Good. That's good. That's-\nCREAK\n...That's not good.\nThe crawlspace gives out beneath you. And suddenly you're falling. You're falling...\nYou're. Falling. Down.\nNO.\nYOU CAN'T BE FALLING DOWN.\nDOWN IS BAD.\nDOWN ISN'T RIGHT.\nIT'S NOT RIGHT.\nIT'S NOT FAIR!!!" << endl;
                cout << "\tGAME OVER" << endl << endl;
                gameEndSequence(hashGameStats, trieGameStats, userCurrentPath);
            }
        }
    }

    // DEBUGGING STUFF - COMMENT OUT LATER
    // 1. Display Hashmap Results
    cout << "HASHMAP DATA\n";
    vector<pair<string, int>> hashData;
    hashGameStats.collectVisualData(hashData);
    for (const auto& entry : hashData) {
        cout << "Path [" << entry.first << "]: " << entry.second << " users\n";
    }

    // 2. Display Trie Results
    // Note: Trie uses PathNode struct (pathSoFar, usersPassedThrough)
    cout << "\nTRIE DATA (Prefix Tree)\n";
    vector<PathNode> trieData;
    trieGameStats.collectVisualData(trieData);
    for (const auto& node : trieData) {
        // This will print every prefix/node in the tree
        if (!node.pathSoFar.empty()) {
            cout << "Node [" << node.pathSoFar << "]: " << node.usersPassedThrough << " users passed through\n";
        }
    }

    // 3. Compare Stats for a specific path
    if (!hashData.empty()) {
        string testPath = "BAA";
        cout << "\n\tComparison for Path: " << testPath << "\n";
        
        cout << "\n[HashMap Stats]:";
        hashGameStats.printPerChoiceStatistics(testPath);
        
        cout << "\n[Trie Stats]:";
        trieGameStats.printPerChoiceStatistics(testPath);
    }

    return 0;
}
