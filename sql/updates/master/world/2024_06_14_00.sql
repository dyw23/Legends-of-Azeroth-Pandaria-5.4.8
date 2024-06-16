-- Add column QuestObjectiveId
ALTER TABLE `quest_poi`
ADD COLUMN `QuestObjectiveId` INT UNSIGNED NOT NULL DEFAULT 0 AFTER `objIndex`;

-- Try to populate with reasonable quest objective data
update quest_poi
    inner join
    (
        select questId, min(Id) as id from quest_objective
        where type in (0, 1, 2) # monster, item, game object
        group by questId
        having count(Id) = 1
    ) objective
    on quest_poi.questId = objective.questId
set QuestObjectiveId = objective.id
where objIndex >= 0; # ignore turn-in quest POIs

-- Quest 8325 - Reclaiming Sunstrider Isle
-- fix line break in offer reward text
set @ENTRY := 8325;
update quest_template set OfferRewardText = 'You have successfully completed your first task; for that, you are to be congratulated.  Such success gives me faith that you will turn out better than those young blood elves who fail to heed the lessons of their masters.  Continued success will be rewarded - not only with knowledge, but also with tangible rewards as well.$B$BYour work here, however, is not finished.  There is much more to learn, my young friend... '
where id = @ENTRY;

-- Well Watcher Solanian
-- fix position
set @ENTRY := 15295;
update creature set position_x = 10376.4, position_y = -6406.69, position_z = 49.798, orientation = 3.58665 where id = @ENTRY;

-- Quest 8330 - Solanian's Belongings
-- fix quest poi objective/index
set @ENTRY := 8330;
update quest_poi set objIndex = 0, QuestObjectiveId = 256353 where questId = @ENTRY and id = 1;
update quest_poi set objIndex = 1, QuestObjectiveId = 256354 where questId = @ENTRY and id = 2;
update quest_poi set objIndex = 2, QuestObjectiveId = 256355 where questId = @ENTRY and id = 3;
