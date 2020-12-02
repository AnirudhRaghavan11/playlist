#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _playlistnode{
    char uniqueID[50];
    char songName[50];
    char artistName[50];
    int songLength;
    struct _playlistnode *nextNodePtr;
}PlaylistNode;

typedef 
enum{
    ADD_SONG,
    REMOVE_SONG,
    CHANGE_POSITION,
    SONG_SPECIFIC_ARTIST,
    TOTAL_PLAYLIST_TIME,
    FULL_PLAYLIST,
    QUIT,
} 
Option;

char *actions[7] = {
    "a",
    "r", 
    "c", 
    "s", 
    "t", 
    "o", 
    "q"
};

int getActionID(char action[]){
    int i; 
    for (i = 0; i < 12; i++){
        if (strcmp(action, actions[i]) == 0) return i;
    }
    return i;
}
void PrintMenu(void){
    printf("a - Add song\n");
    printf("r - Remove song\n");
    printf("c - Change position of song\n");
    printf("s - Output songs by a specific artist\n");
    printf("t - Output total playlist time (in seconds)\n");
    printf("o - Output full playlist\n");
    printf("q - Quit\n");
}

void CreatePlaylistNode(PlaylistNode *head, char ID[], char songName[], char artistName[], int songLength);
void InsertPlaylistNodeAfter(PlaylistNode *head, PlaylistNode *newNode);
void SetNextPlaylistNode(PlaylistNode *head, PlaylistNode *next);
PlaylistNode* GetNextPlaylistNode(PlaylistNode *head);
void PrintPlaylistNode(PlaylistNode *head);
void OutputPlaylist(PlaylistNode *head);
PlaylistNode *AddSong(PlaylistNode *head, char ID[], char songName[], char artistName[], int songLength);
PlaylistNode *RemoveSong(PlaylistNode *head, char ID[]);
PlaylistNode *changePosition(PlaylistNode *head);
void specificArtist(PlaylistNode *head, char artistName[]);
int outputTime(PlaylistNode *head);


int main(){

char playlistTitle[50];
printf("Enter playlist's title:");
scanf("%s", playlistTitle);
    char action[50];
    char songName[50];
    int lengthSeconds;
    char nameArtist[50];
    char uniqueID[50];
    int totalPlaylistTime;
    PlaylistNode *playlist = NULL;
    while (1){
        printf("%s PLAYLIST MENU\n", playlistTitle);
        PrintMenu();
        printf("Choose an option\n");
        scanf("%s", action);
        int action_id = getActionID(action);
        if (action_id == QUIT) break;
        switch(action_id){
            case ADD_SONG: 
               printf("Enter song's Unique ID:\n");
                scanf("%s", uniqueID);
                //fflush(stdin);
               printf("Enter song's name:\n");
                scanf("%s", songName);
                printf("Enter artist's name:\n");
                fgets(nameArtist, 50, stdin);
                printf("Enter song's length (in seconds):\n");
                scanf("%d", &lengthSeconds);
                playlist = AddSong(playlist, uniqueID, songName, nameArtist, lengthSeconds);
                break;
            case REMOVE_SONG:
                scanf("%s", uniqueID);
                playlist = RemoveSong(playlist, uniqueID);
                break;
            case CHANGE_POSITION: 
                break;
            case SONG_SPECIFIC_ARTIST: 
                printf("OUTPUT SONGS BY SPECIFIC ARTIST\n");
                printf("Enter artist's name:\n");
                scanf("%s", nameArtist);
                specificArtist(playlist, nameArtist);
                break;
            case TOTAL_PLAYLIST_TIME:
                totalPlaylistTime = outputTime(playlist);
                printf("Total time: %d\n", totalPlaylistTime);
                break;
            case FULL_PLAYLIST:
                OutputPlaylist(playlist);
                break;
        }
        

    }   
    
    return 0;
}



void CreatePlaylistNode(PlaylistNode *head, char ID[], char songName[], char artistName[], int songLength){
    head = (PlaylistNode*)malloc(sizeof(PlaylistNode*));
    strcpy(head->artistName, artistName);
    strcpy(head->songName, songName);
    strcpy(head->uniqueID, ID);
    head->songLength = songLength;
    head->nextNodePtr = NULL;
}
void InsertPlaylistNodeAfter(PlaylistNode *head, PlaylistNode *newNode){
    if (head->nextNodePtr == NULL){
        head->nextNodePtr = newNode;
        newNode->nextNodePtr = NULL;
    }
    else {
        PlaylistNode *middle = head->nextNodePtr;
        middle->nextNodePtr = newNode;
        head->nextNodePtr = newNode;
        newNode->nextNodePtr = middle;
    }
}
// void SetNextPlaylistNode(PlaylistNode *thisNode, PlaylistNode *node){
    // thisNode->uniqueID = node->uniqueID;
    // strcpy(thisNode->artistName, node->artistName);
    // thisNode->songLength = node->songLength;
    // strcpy(newSong->songName, );
    // strcpy(newSong->uniqueID, ID);
    // strcpy(newSong->artistName, artistName);
    // newSong->songLength = songLength;
    // newSong->nextNodePtr = NULL;}

void OutputPlaylist(PlaylistNode *head){
    PlaylistNode *cur = head;
    int i = 1;

    if (head == NULL){
        printf("Playlist is empty\n");
    }
    while (cur != NULL){
        printf("%d\n", i );
        printf("Unique ID: %s\n", cur->uniqueID);
        printf("Song Name: %s\n", cur->songName);
        printf("Artist Name: %s\n", cur->artistName);
        printf("Song Length (in seconds): %d\n", cur->songLength);
        i++;
        cur = cur->nextNodePtr;
    }
}
PlaylistNode *AddSong(PlaylistNode *head, char ID[], char songName[], char artistName[], int songLength){
    PlaylistNode *newSong  = (PlaylistNode*)malloc(sizeof(PlaylistNode));
    PlaylistNode *current;
    strcpy(newSong->songName, songName);
    strcpy(newSong->uniqueID, ID);
    strcpy(newSong->artistName, artistName);
    newSong->songLength = songLength;
    newSong->nextNodePtr = NULL;

    if (head == NULL){
        return newSong;
    }
    else {

        for (current = head; current != NULL; current  = current->nextNodePtr){
            if (current->nextNodePtr == NULL){
                current->nextNodePtr = newSong;
                break;
            }
        }
    }
    return head;
}
PlaylistNode *RemoveSong(PlaylistNode *head, char ID[]){
    PlaylistNode *cur = head; 
    PlaylistNode *prev = head;

    if (strcmp(head->uniqueID, ID) == 0){
        cur = cur->nextNodePtr;
        free(head);
        return cur;

    }
    while (cur != NULL){
        if (strcmp(cur->uniqueID, ID) == 0){
            break;
        }
        prev = cur;
        cur = cur->nextNodePtr;
    }
    PlaylistNode *toBeDeleted = cur;
    prev->nextNodePtr = toBeDeleted->nextNodePtr;
    free(toBeDeleted);
    return head;

}
void specificArtist(PlaylistNode *head, char artistName[]){
    PlaylistNode *cur = head;
    while (cur != NULL){
        if (strcmp(cur->artistName, artistName) == 0){
            printf("Unique ID: %s\n", cur->uniqueID);
            printf("Song Name: %s\n", cur->songName);
            printf("Artist Name: %s\n", cur->artistName);
            printf("Song Length (in Seconds): %d\n", cur->songLength);
        }
        cur = cur->nextNodePtr;
    }
}
int outputTime(PlaylistNode *head){
    int sum; 
    PlaylistNode *cur = head;
    while (cur != NULL){
        sum  = sum + cur->songLength;
        cur  = cur->nextNodePtr;
    }
    return sum;
}
// this function returns the playlist node based on the position number
PlaylistNode *getSongByPos( PlaylistNode *head, int pos ) {
    PlaylistNode *cur = head;
    if( head == NULL )
        return NULL;
    int i = 1;
    while (cur != NULL){
        if (i == pos){
            return cur;
        }
        cur = cur->nextNodePtr;
        i++;
    }
}
int numberOfSongs(PlaylistNode *head){
    int count = 0;
    PlaylistNode *cur = head;
    while (cur != NULL){
        count++;
        cur = cur->nextNodePtr;
    }
    return count;
}


// parameter pos1: The position of the struct that needs to be moved
//parameter pos2: The position that the struct should be moved to
PlaylistNode *changePosition(PlaylistNode *head){
    int pos1 = 0, pos2 = 0;
    int numSongs = numberOfSongs(head);
    printf("Enter song's current position:\n");
    scanf("%d", &pos1);
    PlaylistNode *moveFrom = getSongByPos(head, pos1);//The node that has been selected by the user, and must be moved
    printf("Enter new position for song:\n");
    scanf("%d", &pos2);
    PlaylistNode *tail = getSongByPos(head, numSongs);//The last node in the list, makes it easier to keep track when moving
    PlaylistNode *prevMoveFrom = getSongByPos(head, pos1 - 1);//The node before the selected node 

    //PlaylistNode *moveTo = getSongByPos(head, pos2);
    if (pos2 <= 1){
        prevMoveFrom->nextNodePtr = moveFrom->nextNodePtr;//
        moveFrom->nextNodePtr = head;
        if (moveFrom == tail){
            tail = prevMoveFrom;
        }
        return moveFrom;
    }
    if (pos2 >= numSongs){
        if (moveFrom == head || prevMoveFrom == NULL){
            head = moveFrom->nextNodePtr;
        }

        else {
            prevMoveFrom->nextNodePtr = moveFrom->nextNodePtr;
        }
        tail->nextNodePtr = moveFrom;
        tail = moveFrom;
        tail->nextNodePtr = NULL;
        return head;
    }

}


