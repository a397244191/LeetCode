/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class cmp
{
public:
  bool operator() (const ListNode* lhs, const ListNode* rhs) const
  {
    return lhs->val > rhs->val;
  }
};


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*,vector<ListNode*>,cmp> pq;
        for(int i = 0 ; i < lists.size() ; i++) {
            if(lists[i])
                pq.push(lists[i]);
        }
        ListNode* ans = NULL;
        ListNode* tail = NULL;
        while(!pq.empty()) {
            ListNode* use = pq.top();
            if(!ans) {
                ans = use;
                tail = ans;
            }
            else {
                tail->next = use;
                tail = tail->next;
            }
            pq.pop();
            if(use->next)
                pq.push(use->next);
        }
        return ans;
    }
};