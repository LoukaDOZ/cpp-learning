struct class_t
{
    int pass, total;
    double passRatio, gain;
};

struct Comparator
{
    bool operator()(class_t& a, class_t& b) const
    {
        return a.gain < b.gain;
    }
};

class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents)
    {
        priority_queue<class_t, vector<class_t>, Comparator> queue;
        double totalPassRatio = 0.0;

        for(vector<int> cls: classes)
        {
            class_t c;
            c.pass = cls[0];
            c.total = cls[1];
            c.passRatio = (double) c.pass / c.total;
            c.gain = ((double) (c.pass + 1) / (c.total + 1)) - c.passRatio;

            if(cls[0] < cls[1])
                queue.push(c);
            else
                totalPassRatio += 1.0;
        }

        if(!queue.empty())
        {
            for(int i = 0; i < extraStudents && !queue.empty(); i++)
            {
                class_t c = queue.top();
                queue.pop();

                c.pass++;
                c.total++;
                c.passRatio += c.gain;
                c.gain = ((double) (c.pass + 1) / (c.total + 1)) - c.passRatio;

                queue.push(c);
            }

            while (!queue.empty())
            {
                totalPassRatio += queue.top().passRatio;
                queue.pop();
            }
        }

        return totalPassRatio / classes.size();
    }
};