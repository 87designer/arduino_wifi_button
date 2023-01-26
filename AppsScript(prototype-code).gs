// GET request syntax:
// https://script.google.com/macros/s/<gscript id>/exec?header_here=data_here
//-----------------------------------------------

/* Function doGet: Parse received data from GET request,
  get and store data which is corresponding with header
  row in Google Spreadsheet
*/

function doGet(e) {
  Logger.log( JSON.stringify(e) );  // view parameters
  var result = 'Ok'; // assume success
  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  }
  else {
    var sheet_id = '<replace with google sheet id>';  // Spreadsheet ID
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();  // get Active sheet
    var newRow = sheet.getLastRow() + 1;
    var rowData = [];
    rowData[0] = new Date();  // Timestamp in column A
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'button': //Parameter
          rowData[1] = value; //Value in column B
          result = 'Written on column B';
          break;
        default:
          result = "unsupported parameter";
      }
    }
    Logger.log(JSON.stringify(rowData));

    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }

  return ContentService.createTextOutput(result);
}

function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}
