// Defeat the enemy hero in two minutes.
var enemyHero = this.findNearest(this.findEnemies());
var enemyScared = 0;
var yetispawned = 0;
this.cast("goldstorm");
loop {
    var enemies = this.findEnemies();
    var nearestEnemy = this.findNearest(enemies);
    
    var lastSummon;
    
    // Your hero can collect coins and summon troops.
    if (this.gold >= this.costOf("archer") + 75 && lastSummon !== "archer") {
        this.summon("archer");
        lastSummon = "archer";
    }
    else if (this.gold >= this.costOf("soldier") + 75 && lastSummon !== "solider")
    {
        this.summon("soldier");
        lastSummon = "solider";
    }
    if (enemies.length > 5 && this.gold >= this.costOf("artillery"))
    {
        this.summon("artillery");
    }
    
    // She also commands your allies in battle.
    var friends = this.findFriends();
    for (var friendIndex = 0; friendIndex < friends.length; ++friendIndex) {
        var friend = friends[friendIndex];
        this.command(friend, "attack", friend.findNearest(enemies));
    }
    
    // Use your hero's abilities to turn the tide.
    if (this.distanceTo(enemyHero) < 25 && this.canCast("fear", enemyHero) && !yetispawned)
    {
        this.cast("fear", enemyHero);
        
    }
    else if (this.distanceTo(enemyHero) < 2 && this.isReady("mana-blast"))
    {
        this.manaBlast();
    }
    else if (this.canCast("raise-dead") && this.findCorpses().length > 5 )
    {
        this.jumpTo(this.findNearest(this.findCorpses()));
        this.cast("raise-dead");
    }
    else if (this.distanceTo(enemyHero) < this.attackRange - 20)
    {
        this.attack(enemyHero);
    }
    if (this.distanceTo(this.findNearest(this.findByType("gem", this.findItems()))) < 10)
    {
        this.move(this.findNearest(this.findByType("gem", this.findItems())).pos);
    }
    else if (this.distanceTo(this.findNearest(this.findByType("coin", this.findItems()))) < 10)
    {
        this.move(this.findNearest(this.findByType("coin", this.findItems())).pos);
    }
    else if (this.distanceTo(this.findNearest(this.findEnemies())) < this.attackRange && yetispawned === 0)
    {
        this.attack(this.findNearest(this.findEnemies()));
    }
    else if (this.canCast("goldstorm"))
    {
        this.cast("goldstorm");
        this.move(this.findNearest(this.findByType("coin", this.findItems())).pos);
        this.move(this.findNearest(this.findByType("coin", this.findItems())).pos);
        this.move(this.findNearest(this.findByType("coin", this.findItems())).pos);
    }
    else if (this.distanceTo(this.findNearest(this.findByType("gem", this.findItems()))) < 50)
    {
        this.move(this.findNearest(this.findByType("gem", this.findItems())).pos);
    }
    if (this.now >= 47.5)
    {
        this.say("setting yetispawnwed to 1");
        yetispawned = 1;
        for (var i = 0; friendIndex < friends.length; ++i) {
            friend = friends[friendIndex];
            this.command(friend, "defend", this);
        }
        this.moveXY(random);
    }
    if (this.health < 730 && yetispawned)
    {
        if (this.pos.y > 42)
        {
            if (this.pos.x >= 0 && this.pos.x <= 43)
                this.jumpTo({x: 79, y: 14});
            else
                this.jumpTo({x: 5, y: 7});
        }
        else
        {
            if (this.pos.x >= 0 && this.pos.x <= 43)
                this.jumpTo({x: 79, y: 68});
            else
                this.jumpTo({x: 3, y: 69});
        }
        
    }
    if (this.health < 150 && this.health > 130)
    {
        for (var y = 0; friendIndex < friends.length; ++i) {
            friend = friends[friendIndex];
            this.command(friend, "defend", this);
        }
    }
    if (this.distanceTo(this.findNearest(this.findEnemies())) < 20)
    {
        this.manaBlast();
    }
}
