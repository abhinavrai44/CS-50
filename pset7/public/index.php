<?php

    // configuration
    require("../includes/config.php"); 
    
    if(isset($_SESSION["id"]))
    {
        // get user cash
        $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        $cash = money_format("$%i", $rows[0]["cash"]);
        
        // get users portfolio
        $rows = query("SELECT * FROM Stock_detail WHERE id = ?", $_SESSION["id"]);
        if(count($rows) > 0)
        {
            $positions = [];
            foreach($rows as $row)
            {
                $stock = lookup($row["symbol"]);
                if($stock !== false)
                {
                    $positions[] = [
                        "symbol" => $row["symbol"],
                        "name" => $stock["name"],
                        "shares" => $row["shares"],
                        "price" => money_format("$%i", $stock["price"]),
                        "total" => money_format("$%i", $stock["price"] * $row["shares"])
                    ];
                }
            }
            render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash]);
        }
        else
        // render portfolio
        render("portfolio.php", ["title" => "Portfolio"]);
    }

?>
