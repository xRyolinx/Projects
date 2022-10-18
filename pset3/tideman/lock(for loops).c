



void lock_pairs(void)
{
    for (int i = 0 ; i < pair_count ; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        for (int j = 0 ; j < i ; j++)
        {
            if (locked[pairs[i].loser][pairs[j].winner] == true)
            {
                locked[pairs[i].winner][pairs[i].loser] = false;
                break;
            }
        }
    }

    return;
}