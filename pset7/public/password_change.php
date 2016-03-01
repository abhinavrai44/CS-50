<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["oldpassword"]))
        {
            apologize("Old password must be provided");
        }
        else if (empty($_POST["newpassword"]))
        {
            apologize("New password must be provided");
        }
        else if (($_POST["confirmation"] != $_POST["newpassword"]))
        {
            apologize("New password must match the confirmation password.");
        }
        
        // get old password hash
        $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        $pass = $rows[0]["hash"];
        
        // compare old and new password
        if (crypt($_POST["oldpassword"], $pass) == $pass)
        {
            // change the users password
            query("UPDATE users set hash = ? WHERE id = ?", crypt($_POST["newpassword"]), $_SESSION["id"]);
            
            // redirect to portfolio
            redirect("/");
        }
        else
        {
            apologize("Incorrect Password");
        }
    }
    else
    {
        // else render form
        render("password_change_page.php", ["title" => "Preferences"]);
    }
    
?>
