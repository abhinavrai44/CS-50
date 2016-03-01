<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("No symbol........");
        }
        
        // find the stock
        $stock = lookup($_POST["symbol"]);
       
        $positions = query("SELECT * FROM Stock_detail WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        // delete the stock
        query("DELETE FROM Stock_detail WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        $credit = $stock["price"] * $positions[0]["shares"];
        
        // add money in user's database
        query("UPDATE users set cash = cash + ? WHERE id = ?", $credit, $_SESSION["id"]);
        
        //$date = explode('/', $_POST['date']);
        //$time = mktime(0,0,0,$date[0],$date[1],$date[2]);
        //$mysqldate = date( 'Y-m-d H:i:s', $time );
        
        $sell = "SELL";
        query("INSERT INTO history (id, buysell, symbol, shares, value, amount) VALUES(?, ?, ?, ?, ?, ?)", $_SESSION["id"], $sell, $stock["symbol"], $positions[0]["shares"], $stock["price"], $credit);
        
        // redirect to the portfolio
        redirect("index.php");
    }
    else
    {
        $positions = query("SELECT * FROM Stock_detail WHERE id = ?", $_SESSION["id"]);
        render("sell_page.php", ["title" => "Sell", "positions" => $positions]);
    }
?>
