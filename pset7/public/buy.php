<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("No Symbol..........");
        }
        
        else if (empty($_POST["shares"]))
        {
            apologize("Plz enter the number of shares");
        }
        
        else if (preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            apologize("Number of shares not valid");
        }
        
        // retrieve stock from symbol
        $stock = lookup($_POST["symbol"]);
        if(count($stock) == 3)
        {
            // Cash available 
            $rows = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            $money = $rows[0]["cash"];
            
            // calculate the cost of the transaction
            $price = $stock["price"] * $_POST["shares"];
            
            // ensure the user has enough cash
            if($price <= $money)
            {
                // debit the user's cash
                query("UPDATE users set cash = cash - ? WHERE id = ?", $price, $_SESSION["id"]);
                
                // create/update the position
                query("INSERT INTO Stock_detail (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $stock["symbol"], $_POST["shares"]);
                
                $sell = "BUY";
                query("INSERT INTO history (id, buysell, symbol, shares, value, amount) VALUES(?, ?, ?, ?, ?, ?)", $_SESSION["id"], $sell, $stock["symbol"], $positions[0]["shares"], $stock["price"], $credit);
                
                // redirect to the portfolio
                redirect("index.php");
            }
            else
            {
                apologize("Not enough cash for transaction.");
            }
        }
        else
        {
            apologize("Stock not found.");
        }
    }
    else
    {
        // else render form
        render("buy_page.php", ["title" => "Buy"]);
    }
?>
