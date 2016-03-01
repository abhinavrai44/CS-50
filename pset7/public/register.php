<?php
// configuration
require("../includes/config.php");
// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
// else render form
render("register_form.php", ["title" => "Register"]);
}
// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
// TOD0
if($_POST["username"] == "" || $_POST["password"] == "" || $_POST["confirmation"] == "")
    apologize("Username and password entries must be filled");
    
else if ( $_POST["password"] != $_POST["confirmation"])
    apologize("The 2 passwords do not match");

$rows = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);
if(count($rows) == 0)
    {
    query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)",$_POST["username"], crypt($_POST["password"]));
    $rows = query("Select * from users where username = ?",$_POST["username"]);
    if(count($rows) == 1) 
        { 
        // query ok
        $id = $rows[0]["id"];
        $_SESSION["id"] = $id;
        redirect("/");
        } 
    else 
        {
        // query failed
        apologize("Could not register your account....");
        } 
    }  
else
    apologize("Username already exists. Select another");        
}
?>
