var ttn = require("ttn")
var appID = "sense_pi"
var accessKey = "ttn-account-v2.h8qFXKjleVDMmOT0MExJsOy5w-Kou0PZUu_R1KRuKw4"
ttn.data(appID, accessKey)
  .then(function (client) {
    client.on("uplink", function (devID, payload) {
      console.log("Received uplink from ", devID)
      console.log(payload)
    })
  })
  .catch(function (error) {
    console.error("Error", error)
    process.exit(1)
  })

