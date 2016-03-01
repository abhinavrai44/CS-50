<?php
//requirements
require("../includes/config.php");

// check is form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
    if (empty($_POST["symbol"]))
        {
        apologize("No symbol........");
        }
    
    // get details of the stock    
    $stock = lookup($_POST["symbol"]);
    if(count($stock) == 3)
        {
        render("stock_result.php", ["title" => "Quote", "stock" => $stock]);
        }
    else
        {
        apologize("Stock not found.");
        }
    }
else
{
render("stock_submit.php", ["title" => "Quote"]);
}
?>
