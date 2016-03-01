<?php

    // configuration
    require("../includes/config.php"); 
    
    if(isset($_SESSION["id"]))
    {
        
        // get users transactions
        $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
        if(count($rows) > 0)
        {
            $transactions = [];
            foreach($rows as $row)
            {
                $transactions[] = [
                    "buysell" => $row["buysell"],
                    "symbol" => $row["symbol"],
                    "shares" => $row["shares"],
                    "value" => $row["value"],
                    "amount" => $row["amount"],
                ];
            }
            render("history_page.php", ["title" => "History", "transactions" => $transactions]);
        }
        else
        {
            render("history_page.php", ["title" => "History"]);
        }
    }

?>
