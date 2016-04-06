contract  sexpool
{
    address public Fredrik;
    address public Daniel;
    
    modifier onlyMembers
    {
        if (msg.sender != Fredrik && msg.sender != Daniel) throw;
        _
    }
    
    function sexpool(address initFredrik, address initDaniel)
    {
        Fredrik = initFredrik;
        Daniel = initDaniel;
    }
    
    function payout() onlyMembers {
        uint256 payout = this.balance/2;
        Fredrik.send(payout);
        Daniel.send(payout);
    }
    
    
    function changeAdress(address newAdress) onlyMembers {
        if (msg.sender == Fredrik) {
            Fredrik = newAdress;
        }
        else {
            Daniel = newAdress;
        }
    }
}
