<html>

    <head>

        <link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="/css/styles.css" rel="stylesheet"/>

                    <title>C$50 Finance: Portfolio</title>
        
        <script src="/js/jquery-1.10.2.min.js"></script>
        <script src="/js/bootstrap.min.js"></script>
        <script src="/js/scripts.js"></script>

    </head>

    <body>

        <div class="container">

            <div id="middle">
<ul class="nav nav-pills">
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="deposit.php">Deposit</a></li>
    <li><a href="password_change.php">Password Change</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>

<table class="form-group">
    <thead>
        <table border="1" style="width:100%">
        <tr>
            <td>Symbol</td>
            <td>Name</td>
            <td>Shares</td>
            <td>Price</td>
            <td>TOTAL</td>
        </tr>
    </thead>
    <tbody>
        <?php
            if(isset($positions))
            {        
                foreach($positions as $position)
                {
                    
                    print("<tr>");
                    print("<td>" . $position["symbol"] . "</td>");
                    print("<td>" . $position["name"] . "</td>");
                    print("<td>" . $position["shares"] . "</td>");
                    print("<td>" . $position["price"] . "</td>");
                    print("<td>" . $position["total"] . "</td>");
                    print("</tr>\n");
                   
                }
            }
            
            print("<tr>");
            print("<td colspan=\"4\">CASH</td>");
            print("<td>" . $cash . "</td>");
            print("</tr>");
        ?>
    </tbody>
</table>
</div>
        </div>

    </body>

</html>
