#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Helper function to convert a string to lowercase
void to_lowercase(char *str) {
    while (*str) {
        *str = tolower((unsigned char) *str);
        str++;
    }
}

// Calculate the number of keywords found in the response
int keyword_match_count(const char *response, const char **keywords, int keyword_count) {
    int match_count = 0;
    char response_copy[1024];
    strcpy(response_copy, response);
    to_lowercase(response_copy);

    for (int i = 0; i < keyword_count; i++) {
        char keyword_copy[256];
        strcpy(keyword_copy, keywords[i]);
        to_lowercase(keyword_copy);
        
        if (strstr(response_copy, keyword_copy) != NULL) {
            match_count++;
        }
    }

    return match_count;
}

// Simple similarity function between the user's response and the ideal answer
double calculate_similarity(const char *response, const char *ideal_answer) {
    // Placeholder: a real implementation might use a more complex method like cosine similarity.
    int match_length = 0;
    int response_length = strlen(response);
    int ideal_length = strlen(ideal_answer);

    // Very basic similarity measurement (could be improved with better NLP techniques)
    for (int i = 0; i < response_length && i < ideal_length; i++) {
        if (tolower(response[i]) == tolower(ideal_answer[i])) {
            match_length++;
        }
    }

    return (double) match_length / (response_length > ideal_length ? response_length : ideal_length);
}

// Main function to analyze the response
double analyze_response(const char *response, const char *ideal_answer, const char **keywords, int keyword_count) {
    // Check keyword matches
    int matches = keyword_match_count(response, keywords, keyword_count);
    double keyword_score = (double) matches / keyword_count;

    // Calculate similarity to ideal answer
    double similarity_score = calculate_similarity(response, ideal_answer);

    // Combine scores for a final rating
    double final_rating = (keyword_score + similarity_score) / 2 * 10;  // Scale to 1-10 rating
    return final_rating;
}
