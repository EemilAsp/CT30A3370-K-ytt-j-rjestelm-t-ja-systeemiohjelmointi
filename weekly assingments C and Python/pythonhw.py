####################################################
############## Do not touch this part ##############
from asyncio.windows_events import NULL
from pickle import NONE
import sqlite3
db = sqlite3.connect(r'C:\Users\eemil\Downloads\hw2tennis.db')
cur = db.cursor()
def initializeDB():
    try:
        f = open("sqlcommands.sql", "r")
        commandstring = ""
        for line in f.readlines():
            commandstring+=line
        cur.executescript(commandstring)
    except sqlite3.OperationalError:
        print("Database exists, skip initialization")


def main():
    userInput = -1
    while(userInput != "0"):
        print("\nMenu options:")
        print("1: Print Players")
        print("2: Print Ranking")
        print("3: Print Matches")
        print("4: Search for one player")
        print("5: Move matchdate")
        print("6: Delete player")
        print("0: Quit")
        userInput = input("What do you want to do? ")
        print(userInput)
        if userInput == "1":
            printPlayers()
        if userInput == "2":
            printRanking()
        if userInput == "3":
            printMatches()
        if userInput == "4":
            searchPlayer()
        if userInput == "5":
            moveMatch()
        if userInput == "6":
            deletePlayer()
        if userInput == "0":
            print("Ending software...")
    db.close()        
    return

############## Do not touch part ends ##############
####################################################


############## Please modify the following ##############
def printPlayers():
    print("Printing players")
    """
    Insert the correct Python and SQL commands
    to print all players
    """
    #Start your modifications after this comment
    cur.execute('Select * from player')
    result = cur.fetchall()
    for i in result:
        print(i) 
    return

def printRanking():
    print("Printing ranking")
    """
    Insert the correct Python and SQL commands 
    to print all ranking information
    """
    #Start your modifications after this comment
    cur.execute('Select * from Ranking')
    result = cur.fetchall()
    for i in result:
        print(i)
    return

def printMatches():
    print("Printing matches")
    """ 
    Insert the correct Python and SQL commands 
    to print all ranking information
    """
    #Start your modifications after this comment
    cur.execute('Select * from Matches')
    result = cur.fetchall()
    for i in result:
        print(i)
    return

def searchPlayer():
    playerName = input("What is the player's surname? ")
    """ 
    Insert the correct Python and SQL commands to find the player 
    using the given surname
    """
    #Start your modifications after this comment
    cur.execute('Select playerid, first_name, last_name, nationality, birthdate from Player where last_name=?',[playerName,])
    result = cur.fetchall()
    print('ID:',result[0][0])
    print('First name:',result[0][1])
    print('Last name:',result[0][2])
    
    print('Nationality:',result[0][3])
    print('Birthdate:',result[0][4])
    return

def moveMatch():
    matchID = input("What is the matchID of the match you want to move? ")
    newMatchDate = input ("What is the new matchdate you want to set?")
    
    """ 
    Using the correct Python and SQL comands:
    Change the match date based on the given matchID and new matchdate
    IF a new matchdate is set to NULL, set the winner and result to NULL as well
    """
    #Start your modifications after this comment
    if(newMatchDate == 'NULL'):
        cur.execute('Update Matches Set resultSets=?, matchdate=?, winnerID=? Where matchid=?',[None,None,None,matchID])
    else:
        cur.execute('Update Matches Set matchdate=? Where matchid=?',[newMatchDate,matchID])
    return

def deletePlayer():
    playerID = input("What is the player's PlayerID? ")
    """ 
    Using the correct Python and SQL comands:
    Delete the Player and his Ranking information
    Additionally, set the playerid to NULL in ALL match-data it is found
    """
    #Start your modifications after this comment
    cur.execute('Update Matches Set resultSets=?, matchdate=?, winnerID=? Where matchid=?',[None,None,None,6])
    
    cur.execute('Update Matches Set matchdate=? Where matchid=?',['01/01/2022',12])

    cur.execute('DELETE from Player where playerid=?',[playerID,])
    cur.execute('DELETE from Ranking where FK_playerid=?',[playerID,])
    cur.execute('Update Matches SET FK_playerOne=? where FK_playerOne=?',[None,playerID,])
    cur.execute('Update Matches SET FK_playerTwo=? where FK_playerTwo=?',[None,playerID,])
    cur.execute('Update Matches SET winnerID=? where winnerID=?',[None,playerID,])


main()