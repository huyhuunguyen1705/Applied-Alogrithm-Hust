/*
Given n jobs J={1,…,n}. Each job i has a deadline d(i) and associated profit p(i) if the job is finished before the deadline.
Every job takes the single unit of time, so the minimum possible deadline for any job is 1. It is also noted that no more than one job can be executed at a time.
Select and schedule a subset of jobs of J such that the total profits is maximal.
Input
Line 1: contains a positive integer n (1≤n≤105)
Line i+1 (i=1,…,n) contains d(i) and p(i) (1≤d(i),p(i)≤105)
Output
Write to total profits obtained from the subset of jobs found.
Example:
Input:
4
4 20
2 10
2 40
2 30
Output:
90
*/
#include<bits/stdc++.h>
using namespace std;

struct Job{
    int deadline;
    int profit;
};

bool comparator(Job a, Job b){
    return a.profit > b.profit;
}

int maxProfit(vector<Job>& jobs, int n){
    sort(jobs.begin(), jobs.end(), comparator); // sort the jobs in decreasing order of profit
    //find max deadline
    int maxDeadline = 0;
    for(const auto& job: jobs){
        maxDeadline = max(maxDeadline, job.deadline);
    }

    //initialize time slots
    vector<bool> timeSlots(maxDeadline+1, false);
    int totalProfit = 0;
    for(const auto& job: jobs){
        // tìm thời gain rảnh từ deadline về 1
        for(int t=min(maxDeadline, job.deadline); t>=1; t--){
            if(timeSlots[t] == false){
                timeSlots[t] = true;
                totalProfit += job.profit;
                break;
            }
        }
    }
    return totalProfit;
}

int main(){
    int n; cin>>n;
    vector<Job> jobs(n);
    for(int i=0; i<n; i++){
        cin>>jobs[i].deadline>>jobs[i].profit;
    }
    cout<<maxProfit(jobs, n)<<'\n';
    return 0;
}