require 'sinatra'
require 'httparty'
require 'debugger'
require 'inline'
require 'multi_json'

class Example
  inline(:C) do |builder|
    builder.c "int test1() {
                 int x = 10;
                 return x;
               }"
  end
end

# set :port, 4567

# https://github.com/aj0strow/sinatra-json_body_params
module Sinatra
  module JsonBodyParams

    def self.registered(app)
      app.before do
        params.merge! json_body_params
      end

      app.helpers do
        def json_body_params
          @json_body_params ||= begin
            MultiJson.load(request.body.read.to_s, symbolize_keys: true)
          rescue MultiJson::LoadError
            {}
          end
        end
      end
    end

  end
end

register Sinatra::JsonBodyParams


# SERVER
post "/email_processor" do
   response = Example.new.test1(params[:Subject]) # return array [true, board_state] [bool, 8x8 mattrix]
   if response[0] == true
      HTTParty.post("http://api.mailjet.com/v3/send/message", :body => {to: opponent_email, from: your_maijlet_email, subject: "Your opponenet just moved!", text: "Reply back to send your move. \n Ex. G1 to E4"}, :basic_auth => {username: api_key, password: secret_key})
      #change state of board (array or database)
   else
      HTTParty.post("http://api.mailjet.com/v3/send/message", :body => {to: self_email, from: your_mailjet_email, subject: "That's not a legal move!", text: "Try again. \n Ex. G1 to E4"}, :basic_auth => {username: api_key, password: secret_key})
      #DO NOT change state of board (array or database)
   end
end
