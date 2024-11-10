/*
Description
Data about submission of a programming contest consists a sequence of lines, each line has the following information:
                                                      <UserID> <ProblemID> <TimePoint> <Status> <Point>
in which the user <UserID> submits his/her code to solve the problem <ProblemID> at time-point <TimePoint>, and gets status <Status> and point <Point>
<UserID>: string of length from 3 to 10
<ProblemID>: string under the format Pxy where x, y are digits 0,1,...,9 (for example P03, P10)
<TimePoint>: string representing time-point with the format HH:MM:SS (for example, 09:45:20 means the time-point 9 hour 45 minutes 20 seconds)
<Status>: string with two cases (ERR, OK)
<Point>: integer from {0, 1, 2, ..., 10}

A user can submit the code for solving each problem several time. The point that the user gets for a problem is the maximal point among the submissions for that problem.

Perform a sequence of queries of following types:
?total_number_submissions: return the number of submissions of the contest
?number_error_submision: return the number of submissions having status ERR 
?number_error_submision_of_user <UserID>: return the number of submission having status ERR of user <UserID> 
?total_point_of_user <UserID>: return the total point of user <UserID> 
?number_submission_period <from_time_point> <to_time_point>: return the number of submissions in the period from <from_time_point> to <to_time_point> (inclusive)

Input
The input consists of two blocks of data:
The first block is the operational data, which is a sequence of lines (number of lines can be up to 100000), each line contains the information of a submission with above format .The first block is terminated with a line containing the character #
The second block is the query block, which is a sequence of lines (number of lines can be up to 100000), each line is a query described above. The second block is terminated with a line containing the character #

Output
Write in each line, the result of the corresponding query 

Example
Input
U001 P01 10:30:20 ERR 0
U001 P01 10:35:20 OK 10
U001 P02 10:40:20 ERR 0
U001 P02 10:55:20 OK 7
U002 P01 10:40:20 ERR 0
U001 P01 11:35:20 OK 8
U002 P02 10:40:20 OK 10
#
?total_number_submissions
?number_error_submision
?number_error_submision_of_user U002 
?total_point_of_user U001 
?number_submission_period 10:00:00 11:30:45
#


Output 
7
3
1
17
6
*/

#include <bits/stdc++.h>

using namespace std;

int totalSubmissions = 0;
int totalErrorSubmissions = 0;

map<string, int> errorSubmissionsOfUser;
map<string, map<string, int>> PointOfUserProblem;
map<string, int> numberSubmissionAtTimePoint;
map<string, int> cumulativeSubmission;

// Struct to hold submission information
struct Submission {
    string userID;
    string problemID;
    string timePoint;
    string status;
    int point;
};

int main(){
    string line;
    // Input processing
    while(getline(cin, line)){
        if(line == "#") break;
        
        stringstream ss(line);
        Submission submission;
        ss >> submission.userID >> submission.problemID >> submission.timePoint >> submission.status >> submission.point;
        totalSubmissions++;
        if(submission.status == "ERR"){
            totalErrorSubmissions++;
            errorSubmissionsOfUser[submission.userID]++;
        }else{
            PointOfUserProblem[submission.userID][submission.problemID] = max(PointOfUserProblem[submission.userID][submission.problemID], submission.point);
        }
        numberSubmissionAtTimePoint[submission.timePoint]++;
    }

    // calculate cumulative submission
    int runningTotal = 0;
    for(const auto& entry : numberSubmissionAtTimePoint){
        runningTotal += entry.second;
        cumulativeSubmission[entry.first] = runningTotal;
    }

    // Query processing
    while(getline(cin, line)){
        if(line == "#") break;
        stringstream ss(line);
        string queryType;
        ss >> queryType;
        if(queryType == "?total_number_submissions"){
            cout << totalSubmissions << endl;
        }else if(queryType == "?number_error_submision"){
            cout << totalErrorSubmissions << endl;
        }else if(queryType == "?number_error_submision_of_user"){
            string userID;
            ss >> userID;
            cout << errorSubmissionsOfUser[userID] << endl;
        }else if(queryType == "?total_point_of_user"){
            string userID;
            ss >> userID;
            int totalPoint = 0;
            for(const auto& entry : PointOfUserProblem[userID]){
                totalPoint += entry.second;
            }
            cout << totalPoint << endl;
        }else if(queryType == "?number_submission_period"){
            string fromTimePoint, toTimePoint;
            ss >> fromTimePoint >> toTimePoint;
            int periodSubmission = 0;

            // Find cumulative submission up to and including `toTime`
            auto toIt = cumulativeSubmission.upper_bound(toTimePoint);
            if (toIt != cumulativeSubmission.begin()) {
                --toIt; // Move to the largest time <= toTime
                periodSubmission = toIt->second;
            }

            // Subtract cumulative submission just before `fromTime`, if applicable
            auto fromIt = cumulativeSubmission.lower_bound(fromTimePoint);
            if (fromIt != cumulativeSubmission.begin()) {
                --fromIt; // Move to the largest time < fromTime
                periodSubmission -= fromIt->second;
            }
            
            cout << periodSubmission << endl;
        }
    }
    return 0;
}
