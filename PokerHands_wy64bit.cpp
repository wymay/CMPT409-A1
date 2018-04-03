// PokerHands

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// change card string to int value
void convertCardsToValue(vector<string>& cards, vector<int>& values){
    for(int i = 0; i < 5; i++){
        string tmpstr = cards[i];
        int valueNoSuit;
        if(tmpstr[0] >= '2' && tmpstr[0] <= '9'){
            valueNoSuit = tmpstr[0] - '2';
        }
        if(tmpstr[0] == 'T'){
            valueNoSuit = 8;
        }
        if(tmpstr[0] == 'J'){
            valueNoSuit = 9;
        }
        if(tmpstr[0] == 'Q'){
            valueNoSuit = 10;
        }
        if(tmpstr[0] == 'K'){
            valueNoSuit = 11;
        }
        if(tmpstr[0] == 'A'){
            valueNoSuit = 12;
        }
        if(tmpstr[1] == 'C'){
            values.push_back(valueNoSuit);
        }
        if(tmpstr[1] == 'D'){
            values.push_back(valueNoSuit + 13);
        }
        if(tmpstr[1] == 'H'){
            values.push_back(valueNoSuit + 13*2);
        }
        if(tmpstr[1] == 'S'){
            values.push_back(valueNoSuit + 13*3);
        }
    }
}

bool isStrightFlush(long long value64bit, vector<int>& comparingValue){
    for(int j = 0; j < 4; j++){
        for(int  i = 0; i < 9; i++){
            int suitOffset = 13*j;
            long long checkSF = 1LL<<(63-(10+i+suitOffset)) | 1LL<<(63-(10+i+1+suitOffset)) |  1LL<<(63-(10+i+2+suitOffset)) | 1LL<<(63-(10+i+3+suitOffset)) | 1LL<<(63-(10+i+4+suitOffset));
            if((value64bit & checkSF) == checkSF){
                comparingValue.push_back(i+4);
                return true;
            }
        }
    }
    return false;
}

bool isFourOfAKind(long long value64bit, vector<int>& comparingValue){
    for(int i = 0; i < 13; i++){
        int suitOffset = 13;
        long long checkFK = 1LL<<(63-(10+i)) | 1LL<<(63-(10+i+suitOffset)) | 1LL<<(63-(10+i+suitOffset*2)) | 1LL<<(63-(10+i+suitOffset*3));
        if((value64bit & checkFK) == checkFK){
            comparingValue.push_back(i);
            return true;
        }
    }
    return false;
}

vector<int> countRepeating(long long value64bit){
    vector<int> count;
    for(int i = 0; i < 13; i++){
        int suitOffset = 13;
        int iCount = (value64bit>>(63-(10+i))&1) +  (value64bit>>(63-(10+i+suitOffset))&1) + (value64bit>>(63-(10+i+suitOffset*2))&1) + (value64bit>>(63-(10+i+suitOffset*3))&1);
        count.push_back(iCount);
    }
    return count;
}

bool isFullHouse(long long value64bit, vector<int>& comparingValue){
    vector<int> count = countRepeating(value64bit);
    std::vector<int>::iterator itThree;
    itThree = find(count.begin(), count.end(), 3);
    std::vector<int>::iterator itPair;
    itPair = find(count.begin(), count.end(), 2);
    if(itThree != count.end() && itPair != count.end()){
        comparingValue.push_back(itThree - count.begin());
        return true;
    }
    return false;
}

bool isFlush(long long value64bit, vector<int>& comparingValue){
    for(int j = 0; j < 4; j++){
        int count = 0;
        for(int i = 0; i < 13; i++){
            int checkBit = value64bit>>(63-(10+i+j*13))&1;
            if(checkBit == 1){
                count++;
                comparingValue.insert(comparingValue.begin(),i);
            }
        }
        if(count == 5){
            return true;
        }
        else{
            comparingValue.clear();
        }
    }
    return false;
}

bool isStright(long long value64bit, vector<int>& comparingValue){
    long long tmp = value64bit | value64bit<<13 | value64bit<<(13*2) | value64bit<<(13*3);
    for(int  i = 0; i < 9; i++){
        long long checkSF = 1LL<<(63-(10+i)) | 1LL<<(63-(10+i+1)) |  1LL<<(63-(10+i+2)) | 1LL<<(63-(10+i+3)) | 1LL<<(63-(10+i+4));
        if((tmp & checkSF) == checkSF){
            comparingValue.push_back(i+4);
            return true;
        }
    } 
    return false;
}

bool isThreeOfAKind(long long value64bit, vector<int>& comparingValue){
    vector<int> count = countRepeating(value64bit);
    std::vector<int>::iterator itThree;
    itThree = find(count.begin(), count.end(), 3);
    if(itThree != count.end()){
        comparingValue.push_back(itThree - count.begin());
        return true;
    }
    return false;
}

bool isTwoPairs(long long value64bit, vector<int>& comparingValue){
    vector<int> count = countRepeating(value64bit);
    std::vector<int>::iterator itPair;
    itPair = find(count.begin(), count.end(), 2);
    if(itPair != count.end()){
        std::vector<int>::iterator itPair2;
        itPair2 = find(++itPair, count.end(), 2);
        if(itPair2 != count.end()){
            comparingValue.push_back(itPair2 - count.begin());
            comparingValue.push_back(itPair - count.begin());
            std::vector<int>::iterator itPair1;
            itPair1 = find(count.begin(), count.end(), 1);
            comparingValue.push_back(itPair1 - count.begin());
            return true;
        }   
    }
    return false;
}

bool isPair(long long value64bit, vector<int>& comparingValue){
    vector<int> count = countRepeating(value64bit);
    std::vector<int>::iterator itPair;
    itPair = find(count.begin(), count.end(), 2);
    if(itPair != count.end()){
        comparingValue.push_back(itPair - count.begin());
        std::vector<int>::iterator it;
        it = count.begin();
        for(int i = 0; i < 3; i++){
            comparingValue.insert(comparingValue.begin()+1, find(it, count.end(), 1)-count.begin());
            it = find(it, count.end(), 1)+1;
        }
        return true;
    }
    return false;
}



int main()
{
    int i = 0;
    string str;

    // read a line and check the line is not empty
    while(getline(cin, str) && str.length() > 0)
    {
        vector<string> black_cards, white_cards;
        stringstream ss(str);
        string substr;

        // read first 5 cards for Black
        for(int i = 0; i < 5; i++)
        {
            getline( ss, substr, ' ');
            black_cards.push_back(substr);
        }

        // read first 5 cards for White
        for(int i = 0; i < 5; i++)
        {
            getline( ss, substr, ' ');
            white_cards.push_back(substr);
        }

        // change card string to int value
        vector<int> blackCardsValue, whiteCardsValue;
        convertCardsToValue(black_cards, blackCardsValue);
        convertCardsToValue(white_cards, whiteCardsValue);
        
        // represent card value in a 64-bit integer
        int cardValueOffset = 10;
        long long black64bit = 0;
        long long white64bit = 0;
        for(int i = 0; i < 5; i++){
            black64bit |= 1LL << (63 - (cardValueOffset + blackCardsValue[i]));
            white64bit |= 1LL << (63 - (cardValueOffset + whiteCardsValue[i]));
        }
        
        // decide poker hands type
        vector<int> blackComparingValue, whiteComparingValue;
        if(isStrightFlush(black64bit, blackComparingValue)){
            black64bit |= (1LL << 62);
        }
        else if(isFourOfAKind(black64bit, blackComparingValue)){
            black64bit |= (1LL << 61);
        }
        else if(isFullHouse(black64bit, blackComparingValue)){
            black64bit |= (1LL << 60);
        }
        else if(isFlush(black64bit, blackComparingValue)){
            black64bit |= (1LL << 59);
        }
        else if(isStright(black64bit, blackComparingValue)){
            black64bit |= (1LL << 58);
        }
        else if(isThreeOfAKind(black64bit, blackComparingValue)){
            black64bit |= (1LL << 57);
        }
        else if(isTwoPairs(black64bit, blackComparingValue)){
            black64bit |= (1LL << 56);
        }
        else if(isPair(black64bit, blackComparingValue)){
            black64bit |= (1LL << 55);
        }
        else{
            long long tmp = black64bit | black64bit<<13 | black64bit<<(13*2) | black64bit<<(13*3);
            for(int  i = 0; i < 13; i++){
                long long checkSF = 1LL << (63-(10+i));
                if((tmp & checkSF) == checkSF){
                    blackComparingValue.insert(blackComparingValue.begin(),i); 
                }
            }
        }


        if(isStrightFlush(white64bit, whiteComparingValue)){
            white64bit |= (1LL << 62);
        }
        else if(isFourOfAKind(white64bit, whiteComparingValue)){
            white64bit |= (1LL << 61);
        }
        else if(isFullHouse(white64bit, whiteComparingValue)){
            white64bit |= (1LL << 60);
        }
        else if(isFlush(white64bit, whiteComparingValue)){
            white64bit |= (1LL << 59);
        }
        else if(isStright(white64bit, whiteComparingValue)){
            white64bit |= (1LL << 58);
        }
        else if(isThreeOfAKind(white64bit, whiteComparingValue)){
            white64bit |= (1LL << 57);
        }
        else if(isTwoPairs(white64bit, whiteComparingValue)){
            white64bit |= (1LL << 56);
        }
        else if(isPair(white64bit, whiteComparingValue)){
            white64bit |= (1LL << 55);
        }
        else{
            long long tmp = white64bit | (white64bit<<13) | (white64bit<<(13*2)) | (white64bit<<(13*3));
            for(int  i = 0; i < 13; i++){
                long long checkSF = 1LL << (63-(10+i));
                if((tmp & checkSF) == checkSF){
                    whiteComparingValue.insert(whiteComparingValue.begin(),i); 
                }
            }   
        }

        if((black64bit>>54) > (white64bit>>54)){
            printf("Black wins.\n");
        }
        else if((black64bit>>54) < (white64bit>>54)){
            printf("White wins.\n");
        }
        else{
            for(i = 0; i < blackComparingValue.size(); i++){
                if(blackComparingValue[i] > whiteComparingValue[i]){
                    printf("Black wins.\n");
                    break;
                }
                if(blackComparingValue[i] < whiteComparingValue[i]){
                    printf("White wins.\n");
                    break;
                }
            }
            if(i == blackComparingValue.size()){
                printf("Tie.\n");
            }
        }
    }
    return 0;
}