-- Add column QuestObjectiveId
ALTER TABLE `quest_poi`
ADD COLUMN IF NOT EXISTS `QuestObjectiveId` INT UNSIGNED NOT NULL DEFAULT 0 AFTER `objIndex`;

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
where objIndex >= 0 # ignore turn-in quest POIs
